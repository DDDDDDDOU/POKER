// yfs client.  implements FS operations using extent and lock server
#include "yfs_client.h"
#include "extent_client.h"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

yfs_client::yfs_client(string extent_dst, string lock_dst)
{
    ec = new extent_client(extent_dst);
    // Lab2: Use lock_client_cache when you test lock_cache
    // lc = new lock_client(lock_dst);
    lc = new lock_client_cache(lock_dst);
    lc->acquire(1);
    if (ec->put(1, "") != extent_protocol::OK)
        printf("error init root dir\n"); // XYB: init root dir
    lc->release(1);
}

yfs_client::inum
yfs_client::n2i(string n)
{
    istringstream ist(n);
    unsigned long long finum;
    ist >> finum;
    return finum;
}

string
yfs_client::filename(inum inum)
{
    ostringstream ost;
    ost << inum;
    return ost.str();
}

bool
yfs_client::isfile(inum inum)
{
    extent_protocol::attr a;
    lc->acquire(inum);
    if (ec->getattr(inum, a) != extent_protocol::OK) {
        printf("error getting attr\n");
        lc->release(inum);
        return false;
    }
    lc->release(inum);

    if (a.type == extent_protocol::T_FILE) {
        printf("isfile: %lld is a file\n", inum);
        return true;
    }
    printf("isfile: %lld is not a file\n", inum);
    return false;
}
/** Your code here for Lab...
 * You may need to add routines such as
 * readlink, issymlink here to implement symbolic link.
 *
 * */

bool
yfs_client::isdir(inum inum)
{
    extent_protocol::attr a;
    lc->acquire(inum);
    if (ec->getattr(inum, a) != extent_protocol::OK) {
        printf("error getting attr\n");
        lc->release(inum);
        return false;
    }
    lc->release(inum);
    if (a.type == extent_protocol::T_DIR) {
        printf("isfile: %lld is a dir\n", inum);
        return true;
    }
    printf("isfile: %lld is not a dir\n", inum);
    return false;
}

bool
yfs_client::issymlink(inum inum)
{
    extent_protocol::attr a;
    lc->acquire(inum);
    if (ec->getattr(inum, a) != extent_protocol::OK) {
        printf("error getting attr\n");
        lc->release(inum);
        return false;
    }
    lc->release(inum);
    if (a.type == extent_protocol::T_SYMLINK) {
        printf("isfile: %lld is a symlink\n", inum);
        return true;
    }
    printf("isfile: %lld is not a symlink\n", inum);
    return false;
}

int
yfs_client::getfile(inum inum, fileinfo &fin)
{
    int r = OK;

    printf("getfile %016llx\n", inum);
    extent_protocol::attr a;
    lc->acquire(inum);
    if (ec->getattr(inum, a) != extent_protocol::OK) {
        r = IOERR;
        lc->release(inum);
        return r;
    }
    lc->release(inum);

    fin.atime = a.atime;
    fin.mtime = a.mtime;
    fin.ctime = a.ctime;
    fin.size = a.size;
    printf("getfile %016llx -> sz %llu\n", inum, fin.size);


    return r;
}

int
yfs_client::getdir(inum inum, dirinfo &din)
{
    int r = OK;

    printf("getdir %016llx\n", inum);
    extent_protocol::attr a;
    lc->acquire(inum);
    if (ec->getattr(inum, a) != extent_protocol::OK) {
        r = IOERR;
        goto release;
    }
    
    din.atime = a.atime;
    din.mtime = a.mtime;
    din.ctime = a.ctime;

release:
lc->release(inum);
    return r;
}


#define EXT_RPC(xx) do { \
    if ((xx) != extent_protocol::OK) { \
        printf("EXT_RPC Error: %s:%d \n", __FILE__, __LINE__); \
        r = IOERR; \
        goto release; \
    } \
} while (0)

// Only support set size of attr
int
yfs_client::setattr(inum ino, size_t size)
{
    int r = OK;

    /*
     * your code goes here.
     * note: get the content of inode ino, and modify its content
     * according to the size (<, =, or >) content length.
     */
    
    string buf;
    lc->acquire(ino);
    if ((r=ec->get(ino, buf))!=OK){
        printf("no such file!\n");
        lc->release(ino);
        return r;
    };
    
    buf.resize(size);
    
    if((r=ec->put(ino, buf))!=OK){
        printf("file write error!\n");
        lc->release(ino);
        return r;
    };
    lc->release(ino);
    return r;
}

int
yfs_client::create(inum parent, const char *name, mode_t mode, inum &ino_out)
{
    int r = OK;

    /*
     * your code goes here.
     * note: lookup is what you need to check if file exist;
     * after create file or dir, you must remember to modify the parent infomation.
     */
    lc->acquire(parent);
    bool found ;
    lookup(parent, name, found, ino_out);
    if (found) {
        lc->release(parent);
            ///here!
        return EXIST;
    }
    ec->create(extent_protocol::T_FILE, ino_out);
    string buffer;
    ec->get(parent, buffer);
    buffer.append(string(name) + ":" + filename(ino_out) + "/");
    ec->put(parent, buffer);
    lc->release(parent);
    return r;
}

int
yfs_client::mkdir(inum parent, const char *name, mode_t mode, inum &ino_out)
{
    int r = OK;

    /*
     * your code goes here.
     * note: lookup is what you need to check if directory exist;
     * after create file or dir, you must remember to modify the parent infomation.
     */

    // check if dir name has existed
    bool found ;
  lc->acquire(parent);
    lookup(parent, name, found, ino_out);
    if (found)  {
    lc->release(parent);

        return EXIST;
    }
    ec->create(extent_protocol::T_DIR, ino_out);
    string buffer;
    ec->get(parent, buffer);
    buffer.append(string(name) + ":" + filename(ino_out) + "/");
    ec->put(parent, buffer);
    lc->release(parent);
    return r;
}

int
yfs_client::lookup(inum parent, const char *name, bool &found, inum &ino_out)
{
    int r = OK;

    /*
     * your code goes here.
     * note: lookup file from parent dir according to name;
     * you should design the format of directory content.
     */

    list<dirent> entrys;
    readdir(parent, entrys);
    if (entrys.size()==0) {
        found = false;
        return r;
    }

    for (std::list<dirent>::iterator it = entrys.begin(); it != entrys.end(); it++) {
        if (it->name.compare(name) == 0) {
            // exist
            found = true;
            ino_out = it->inum;
            return r;
        }
    }
    found = false;
    return r;
}

int yfs_client::readdir(inum dir, list<dirent> &list)
{
    int r = OK;

    /*
     * your code goes here.
     * note: you should parse the dirctory content using your defined format,
     * and push the dirents to the list.
     */
    // my format of dir content: "name:inum/name:inum/name:inum/"

    // get directory content
    string buf;
    // lc->acquire(dir);
    ec->get(dir, buf);
    // lc->release(dir);
    int name_start = 0;
    int name_end = buf.find(':',name_start);
    int end=0;

    while (name_end != string::npos) {
        end=buf.find('/',name_start);

        string name=buf.substr(name_start,name_end-name_start);
        string inum=buf.substr(name_end+1,end-name_end);
    
        struct dirent entry;
        entry.name = name;
        entry.inum = n2i(inum);

        list.push_back(entry);
        name_start = end + 1;
        name_end=buf.find(':',name_start);
    }

    return r;
}

int
yfs_client::read(inum ino, size_t size, off_t off, string &data)
{
    int r = OK;

    /*
     * your code goes here.
     * note: read using ec->get().
     */
    
    string buf;
    lc->acquire(ino);
    ec->get(ino, buf);  // read the whole file
    lc->release(ino);
    // off > file size
    if (off > buf.size()) {
        data = "";
        return r;
    }

    if (off + size > buf.size()) {
        data = buf.substr(off);
    }
    else data = buf.substr(off, size);
    return r;
}

int
yfs_client::write(inum ino, size_t size, off_t off, const char *data,
        size_t &bytes_written)
{
    int r = OK;

    /*
     * your code goes here.
     * note: write using ec->put().
     * when off > length of original file, fill the holes with '\0'.
     */
    
    string buf;
    lc->acquire(ino);
    ec->get(ino, buf);
    if(off+size >buf.size()) buf.resize(off+size);
    for (int i = off; i < off + size; i++) {
        buf[i] = data[i - off];
    }
    bytes_written = size;
    ec->put(ino, buf);
    lc->release(ino);
    return r;
}

int yfs_client::unlink(inum parent,const char *name)
{
    int r = OK;

    /*
     * your code goes here.
     * note: you should remove the file using ec->remove,
     * and update the parent directory content.
     */
    lc->acquire(parent);
    bool found = false;  // not necessary
    inum inum;
    lookup(parent, name, found, inum);
    

    ec->remove(inum);
    string buf;
  
    ec->get(parent, buf);
    int start = buf.find(name);
    int after = buf.find('/', start);
    buf.erase(start, after - start + 1);
    ec->put(parent, buf);
    lc->release(parent);

    return r;
}

int yfs_client::symlink(inum parent, const char *name, const char *link, inum &ino_out)
{
    int r = OK;
    lc->acquire(parent);
    bool found = false;
    inum tmp;
    lookup(parent, name, found, tmp);
    if (found)         {
        lc->release(parent);

        return EXIST;
        }
    
    ec->create(extent_protocol::T_SYMLINK, ino_out);
    ec->put(ino_out, string(link));

    string buf;

    ec->get(parent, buf);
    buf.append(string(name) + ":" + filename(ino_out) + "/");
    ec->put(parent, buf);
    lc->release(parent);
    return r;
}

int yfs_client::readlink(inum ino, string &data)
{
    int r = OK;
    string buf;
    lc->acquire(ino);
    ec->get(ino, buf);
    data = buf;
    lc->release(ino);
    return r;
}
