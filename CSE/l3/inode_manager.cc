#include "inode_manager.h"

// disk layer -----------------------------------------

disk::disk()
{
  bzero(blocks, sizeof(blocks));
}

void
disk::read_block(blockid_t id, char *buf)
{

  if(id<0 || id>=BLOCK_NUM){
    printf("error id!\n");
  }
  memcpy(buf,blocks[id],BLOCK_SIZE);
  return;

}

void
disk::write_block(blockid_t id, const char *buf)
{

  if(id<0 || id>=BLOCK_NUM){
    printf("error id!\n");
  }
  memcpy(blocks[id],buf,BLOCK_SIZE);
  return;
}

// block layer -----------------------------------------

// Allocate a free disk block.
blockid_t
block_manager::alloc_block()
{
  /*
   * your code goes here.
   * note: you should mark the corresponding bit in block bitmap when alloc.
   * you need to think about which block you can start to be allocated.
   */

  
  int offset=0;
  for(offset;;offset++){
    if(offset+IBLOCK(INODE_NUM,BLOCK_NUM)>=BLOCK_NUM) {
      printf("no block \n");
      exit(0);
    }
    char buffer[BLOCK_SIZE];
    read_block(BBLOCK(offset),buffer);
    if((buffer[offset/8] & (1<<(7-offset%8)) )==0 ){
      buffer[offset/8]=buffer[offset/8] | ((unsigned char)(1<<(7-offset%8))) ;
      write_block(BBLOCK(offset),buffer);
      return IBLOCK(INODE_NUM,BLOCK_NUM)+offset;
    }


  }



  return 0;
}

void
block_manager::free_block(uint32_t id)
{
  /*
   * your code goes here.
   * note: you should unmark the corresponding bit in the block bitmap when free.
   */




  if(id<0 || id>=BLOCK_NUM){
    printf("error Id\n");
    return;
  }
  int offset=id-IBLOCK(INODE_NUM,BLOCK_NUM);
  char buffer[BLOCK_SIZE];
  read_block(BBLOCK(offset),buffer);
  buffer[offset/8]= (~((~buffer[offset/8]) | ((unsigned char)(1<<(7-offset%8))) )); //set bit
  write_block(BBLOCK(offset),buffer);


  
  return;
}

// The layout of disk should be like this:
// |<-sb->|<-free block bitmap->|<-inode table->|<-data->|
block_manager::block_manager()
{
  d = new disk();

  // format the disk
  sb.size = BLOCK_SIZE * BLOCK_NUM;
  sb.nblocks = BLOCK_NUM;
  sb.ninodes = INODE_NUM;

  // for(int i=0;i<sb.nblocks;++i){
  //   using_blocks[i]=0;
  // }
  // using_blocks[0]=1;
  // using_blocks[1]=1;
  // using_blocks[2]=1;
  // using_blocks[3]=1;
  

}

void
block_manager::read_block(uint32_t id, char *buf)
{
  d->read_block(id, buf);
}

void
block_manager::write_block(uint32_t id, const char *buf)
{
  d->write_block(id, buf);
}

// inode layer -----------------------------------------

inode_manager::inode_manager()
{
  bm = new block_manager();
  uint32_t root_dir = alloc_inode(extent_protocol::T_DIR);
  if (root_dir != 1) {
    printf("\tim: error! alloc first inode %d, should be 1\n", root_dir);
    exit(0);
  }
}

/* Create a new file.
 * Return its inum. */
uint32_t
inode_manager::alloc_inode(uint32_t type)
{
  /*
   * your code goes here.
   * note: the normal inode block should begin from the 2nd inode block.
   * the 1st is used for root_dir, see inode_manager::inode_manager().
   */

  int inodenum=0;
  while(get_inode(++inodenum)!=NULL);

  inode *i;
  i=(inode*) malloc(sizeof(inode));
  i->type=type;
  i->size=0;
  i->atime=(unsigned int)time(NULL);
  i->mtime=(unsigned int)time(NULL);
  i->ctime=(unsigned int)time(NULL);

  put_inode(inodenum,i);
  free(i);
  return inodenum;


}

void
inode_manager::free_inode(uint32_t inum)
{
  /*
   * your code goes here.
   * note: you need to check if the inode is already a freed one;
   * if not, clear it, and remember to write back to disk.
   */

  struct inode *inode;
  if ((inode = get_inode(inum)) == NULL) {
    return;
  }

  inode->type = 0;
  put_inode(inum, inode);
  free(inode); //sibalaxi
  return;
}


/* Return an inode structure by inum, NULL otherwise.
 * Caller should release the memory. */
struct inode*
inode_manager::get_inode(uint32_t inum)
{
  struct inode *inode, *ino_disk;
  char buf[BLOCK_SIZE];

  printf("\tim: get_inode %d\n", inum);

  if (inum < 0 || inum >= INODE_NUM) {
    printf("\tim: inum out of range\n");
    return NULL;
  }

  bm->read_block(IBLOCK(inum, bm->sb.nblocks), buf);
  // printf("%s:%d\n", __FILE__, __LINE__);

  ino_disk = (struct inode*)buf + inum%IPB;
  if (ino_disk->type == 0) {
    printf("\tim: inode not exist\n");
    return NULL;
  }

  inode = (struct inode*)malloc(sizeof(struct inode));
  *inode = *ino_disk;

  return inode; //should be freed
}

void
inode_manager::put_inode(uint32_t inum, struct inode *inode)
{
  char buf[BLOCK_SIZE];
  struct inode *ino_disk;

  printf("\tim: put_inode %d\n", inum);
  if (inode == NULL)
    return;

  bm->read_block(IBLOCK(inum, bm->sb.nblocks), buf);
  ino_disk = (struct inode*)buf + inum%IPB;
  *ino_disk = *inode;
  bm->write_block(IBLOCK(inum, bm->sb.nblocks), buf);
}

#define MIN(a,b) ((a)<(b) ? (a) : (b))

/* Get all the data of a file by inum.
 * Return alloced data, should be freed by caller. */
void
inode_manager::read_file(uint32_t inum, char **buf_out, int *size)
{
  /*
   * your code goes here.
   * note: read blocks related to inode number inum,
   * and copy them to buf_Out
   */



  inode_t *inode = get_inode(inum);
  *buf_out = (char *)malloc(inode->size);
  *size=0;
  char buf[BLOCK_SIZE];

  if (inode->size == 0) {
    inode->atime = (unsigned int)time(NULL);
    put_inode(inum, inode);
    free(inode);
    return;
  }
  if (inode->size <= NDIRECT * BLOCK_SIZE) {
    for (int i = 0; i < (inode->size-1)/BLOCK_SIZE + 1; i++) {
      bm->read_block(inode->blocks[i], buf);
      if (i != (inode->size-1)/BLOCK_SIZE) {
        memcpy(*buf_out + *size, buf, BLOCK_SIZE);
        *size += BLOCK_SIZE;
      }
      else {
        memcpy(*buf_out + *size, buf, ((inode->size-1) % BLOCK_SIZE) + 1);
        *size += ((inode->size-1) % BLOCK_SIZE) + 1;
      }
    }
  }
  else {
    char second[BLOCK_SIZE];
    bm->read_block(inode->blocks[NDIRECT], second);
    for (int i = 0; i < NDIRECT; i++) {
      
      bm->read_block(inode->blocks[i], buf);
      memcpy(*buf_out + *size, buf, BLOCK_SIZE);
      *size += BLOCK_SIZE;
    }

    
    for (int i = 0; i < (inode->size - NDIRECT * BLOCK_SIZE - 1)/BLOCK_SIZE + 1; i++) {
      bm->read_block(*((uint32_t *)second + i), buf);
      if (i != (inode->size - NDIRECT * BLOCK_SIZE - 1)/BLOCK_SIZE) {
        memcpy(*buf_out + *size, buf, BLOCK_SIZE);
        *size += BLOCK_SIZE;
      }
      else {
        memcpy(*buf_out + *size, buf, ((inode->size-1) % BLOCK_SIZE) + 1);
        *size += ((inode->size-1) % BLOCK_SIZE) + 1;
      }
    }
  }
  
  inode->atime = (unsigned int)time(NULL);
  put_inode(inum, inode);
  free(inode);
  return;



  
  // inode_t *inode = get_inode(inum);
  // *buf_out=(char *)malloc(inode->size);
  // *size=0;
  // printf("aae\n");

  // if(inode->size ==0 ){
  //   inode->atime==(unsigned int)time(NULL);
  //   put_inode(inum,inode);
  //   free(inode);
  //   return;
  // }
  // char buffer[BLOCK_SIZE];
  // if(inode->size <= NDIRECT*BLOCK_SIZE){
  //   printf("aab\n");
  //   for(int i=0; i< (inode->size-1)/BLOCK_SIZE;i++ ){
  //     bm->read_block(inode->blocks[i],buffer);
  //     memcpy(*buf_out+*size,buffer,BLOCK_SIZE);
  //     *size+=BLOCK_SIZE;
  //   }
    
  //   bm->read_block(inode->blocks[(inode->size-1)%BLOCK_SIZE],buffer);
  //   memcpy(*buf_out+*size,buffer,((inode->size-1)%BLOCK_SIZE)+1);
  //   *size+=((inode->size-1)%BLOCK_SIZE)+1;
  // }else{
  //   printf("aac\n");
  //   char second[BLOCK_SIZE];
  //   bm->read_block(inode->blocks[NDIRECT],second);
  //   for(int i=0; i< NDIRECT;i++ ){
  //     bm->read_block(inode->blocks[i],buffer);
  //     memcpy(*buf_out+*size,buffer,BLOCK_SIZE);
  //     *size+=BLOCK_SIZE;
  //   }
  //   for(int i=0;i<(inode->size - NDIRECT*BLOCK_SIZE - 1) / BLOCK_SIZE;i++){
  //     bm->read_block(*((uint32_t*)second+i),buffer);
  //     memcpy(*buf_out+*size,buffer,BLOCK_SIZE);
  //     *size+=BLOCK_SIZE;
  //   }
  //   bm->read_block(*((uint32_t*)second+(inode->size - NDIRECT*BLOCK_SIZE - 1) / BLOCK_SIZE),buffer);
  //   memcpy(*buf_out+*size,buffer,((inode->size-1)%BLOCK_SIZE)+1);
  //   *size+=((inode->size-1)%BLOCK_SIZE)+1;
    
  // }
  // printf("aa\n");
  // inode->atime=(unsigned int )time(NULL);
  // put_inode(inum,inode);
  // free(inode);





  // return;
}

/* alloc/free blocks if needed */
void
inode_manager::write_file(uint32_t inum, const char *buf, int size)
{
  /*
   * your code goes here.
   * note: write buf to blocks of inode inum.
   * you need to consider the situation when the size of buf
   * is larger or smaller than the size of original inode
   */
  
  if (size > MAXFILE * BLOCK_SIZE) {
    printf("\tim: file too large\n");
    return;
  }

  inode_t *inode = get_inode(inum); //should be freed
  if (inode->size > 0) {
    if (inode->size <= NDIRECT * BLOCK_SIZE) {
      for (int i = 0; i < (inode->size-1)/BLOCK_SIZE + 1; i++) {
        bm->free_block(inode->blocks[i]);
      }
    }
    else {
      for (int i = 0; i < NDIRECT; i++) {
        bm->free_block(inode->blocks[i]);
      }

      char second[BLOCK_SIZE];
      bm->read_block(inode->blocks[NDIRECT], second);
      for (int i = 0; i < (inode->size - NDIRECT * BLOCK_SIZE - 1)/BLOCK_SIZE + 1; i++) {
        bm->free_block(*((uint32_t *)second + i));
      }
      bm->free_block(inode->blocks[NDIRECT]);
    }
  }

  if (size <= NDIRECT * BLOCK_SIZE) {
    for (int i = 0; i < (size-1)/BLOCK_SIZE + 1; i++) {
      uint32_t tmp = bm->alloc_block();
      bm->write_block(tmp, buf + i * BLOCK_SIZE);
      inode->blocks[i] = tmp;
    }
  }
  else {
    for (int i = 0; i < NDIRECT; i++) {
      uint32_t tmp = bm->alloc_block();
      bm->write_block(tmp, buf + i * BLOCK_SIZE);
      inode->blocks[i] = tmp;
    }

    inode->blocks[NDIRECT] = bm->alloc_block();

    char second[BLOCK_SIZE];
    for (int i = 0; i < (size - NDIRECT * BLOCK_SIZE - 1)/BLOCK_SIZE + 1; i++) {
      uint32_t tmp = bm->alloc_block();
      bm->write_block(tmp, buf + (NDIRECT+i) * BLOCK_SIZE);
      *((uint32_t *)second + i) = tmp;
    }
    bm->write_block(inode->blocks[NDIRECT], second);
  }

  inode->size = size;
  inode->mtime = (unsigned int)time(NULL);
  inode->ctime = (unsigned int)time(NULL);
  inode->atime = (unsigned int)time(NULL);
  
  put_inode(inum, inode);
  free(inode);
  return;
}

void
inode_manager::getattr(uint32_t inum, extent_protocol::attr &a)
{
  /*
   * your code goes here.
   * note: get the attributes of inode inum.
   * you can refer to "struct attr" in extent_protocol.h
   */
  struct inode *inode = get_inode(inum);
  if (inode == NULL) {
    a.type = 0;
    return;
  }
  a.size = inode->size;
  a.type = inode->type;
  a.atime = inode->atime;
  a.mtime = inode->mtime;
  a.ctime = inode->ctime;
  
  
  
  
  return;
}

void
inode_manager::remove_file(uint32_t inum)
{
  /*
   * your code goes here
   * note: you need to consider about both the data block and inode of the file
   */
  
 inode_t *inode = get_inode(inum);//shoud be freed

  if (inode->size > 0) {
    if (inode->size <= NDIRECT * BLOCK_SIZE) {
      for (int i = 0; i < (inode->size-1)/BLOCK_SIZE + 1; i++) {
        bm->free_block(inode->blocks[i]);
      }
    }
    else {
      for (int i = 0; i < NDIRECT; i++) {
        bm->free_block(inode->blocks[i]);
      }
      char second[BLOCK_SIZE];
      bm->read_block(inode->blocks[NDIRECT], second);
      for (int i = 0; i < (inode->size - NDIRECT * BLOCK_SIZE - 1)/BLOCK_SIZE + 1; i++) {
        bm->free_block(*((uint32_t *)second + i));
      }
      bm->free_block(inode->blocks[NDIRECT]);
    }
  }
  free_inode(inum);
  free(inode);
  
  return;
}
