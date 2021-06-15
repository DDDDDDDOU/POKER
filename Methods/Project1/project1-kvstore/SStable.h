#ifndef SS_TABLE
#define SS_TABLE
#include <string>
#include <filesystem>
#include <fstream>
#include <time.h>
#include "node.h"
using namespace std::filesystem;
using namespace std;

struct unit{
    uint64_t key;
    int  pos;
    unit *next;
   
    unit(uint64_t j,int p){key=j;pos=p;next=nullptr;}
    unit(){next=nullptr;}
    void Delete(unit *h){
        if(h->next) Delete(h->next);
        delete h;
    }
    
};
class SStable
{
private: 
    int compacttime;
    int CT;
    int level;
    int *num;
    //int num0;

    struct cell
    {
       // char va[10240];
        string name;
        int socindex;
        string path;
        uint64_t minkey;
        uint64_t maxkey; 
        cell *next; 
        cell *down;      
        cell(){next=nullptr;down=nullptr;}
    };
    cell *head;
    cell* l(int a ,int b){
        if(a>level) return nullptr;
        else{
            cell *tmp=head;
            for(int i=0;i<a;++i){
                tmp=tmp->down;
            }
            for(int i=0;i<b;++i){
                tmp=tmp->next;
            }
            return tmp;
        }
    }
    
public:
    SStable(/* args */);
    void compact(int levelone,int leveltwo);
    void putFileToLevel(node* li,int le);
    void deleteFilefromlevel(cell *f,int le);
    void Remove();
    void putFile(node *h,node *t,int le=0);
    void Delete(node *t);
    void dis(int le);
    void showlist();
    void updatecache();
    void readcache();
    int gettimes(){return compacttime;}
    int gettime(){return CT;}
    string get(uint64_t k);
    ~SStable();
};



#endif // !SS_TABLE
