#include "SStable.h"
#include <iostream>
#include <filesystem>
using namespace std;
using namespace std::filesystem;
void SStable::showlist(){
    cell *flg=head;
    cell *tmp=flg;
    while(flg!=nullptr){
        tmp=flg->next;
        while(tmp!=nullptr){
            cout<<tmp->path<<endl;
            cout<<tmp->minkey<<'\t'<<tmp->maxkey<<endl;
            tmp=tmp->next;
        }
        flg=flg->down;
    }
}

string SStable::get(uint64_t k){
    cell *flg=head;
    cell *tmp=flg;
    fstream in;
    uint64_t ke;
    uint64_t nextke;
    int po; 
    int nextpo;
    string ret="";
    char *va;
    bool level0=false;
    for(int i=0;i<num[0];++i){
        tmp=tmp->next;
        if(k>=tmp->minkey&&k<=tmp->maxkey){
            in.open(tmp->path,ios::in|ios::binary);
            in.seekg(tmp->socindex,ios::beg);
            while(in.read((char*)&ke,sizeof(uint64_t))&&in.read((char*)&po,sizeof(int))){
                if(ke==k){
                    in.read((char*)&nextke,sizeof(uint64_t));
                    in.read((char*)&nextpo,sizeof(int));
                    in.seekg(po+8,ios::beg);
                    va=new char[nextpo-po-7];
                    va[nextpo-po-8]='\0';
                    in.read(va,sizeof(char)*(nextpo-po-8));
                    
                    ret=va;
                    level0=true;//第0层发现目标
                    break;
                }
                if(ke>k) break;
            }
            in.close();
        }
    }
    //int buf;
    if(level0==true) {
        //cout<<"find in level0"<<endl;
       // cin>>buf;
        return ret;}

    flg=flg->down;
    while(flg!=nullptr){
        tmp=flg->next;
        while(tmp!=nullptr){
            if(k>=tmp->minkey&&k<=tmp->maxkey){
                in.open(tmp->path,ios::in|ios::binary);
                in.seekg(tmp->socindex,ios::beg);
                while(in.read((char*)&ke,sizeof(uint64_t))&&in.read((char*)&po,sizeof(int))){
                if(ke==k){
                    in.read((char*)&nextke,sizeof(uint64_t));
                    in.read((char*)&nextpo,sizeof(int));
                    in.seekg(po+8,ios::beg);
                    va=new char[nextpo-po-7];
                    va[nextpo-po-8]='\0';
                    in.read(va,sizeof(char)*(nextpo-po-8));
                    
                    ret=va;
           // cout<<"in sst:"<<endl;
                    return ret;
                }
                if(ke>k) break;
                }
                in.close();
            }
            tmp=tmp->next;
        }

        //if(tmp!=nullptr&&k>=tmp->minkey&&k<=tmp->maxkey) break;
        flg=flg->down;
    }
    //if(flg==nullptr) {
       // cout<<"not in sst"<<endl;
        return "";
    //};

    // in.open(tmp->path,ios::in|ios::binary);
    // in.seekg(tmp->socindex,ios::beg);
    // while(in.read((char*)&ke,sizeof(uint64_t))&&in.read((char*)&po,sizeof(int))){
    //     if(ke==k){
    //         in.read((char*)&nextke,sizeof(uint64_t));
    //         in.read((char*)&nextpo,sizeof(int));
    //         in.seekg(po+8,ios::beg);
    //         va=new char[nextpo-po-7];
    //         va[nextpo-po-8]='\0';
    //         in.read(va,sizeof(char)*(nextpo-po-8));
    //         in.close();
    //         ret=va;
    //        // cout<<"in sst:"<<endl;
    //         return ret;
    //     }
    //     if(ke>k) break;
    // }
    // //cout<<"not in sst"<<endl;
    // return "";



}

void SStable::dis(int le){
    cell *tmp=head;
    for(int i=0;i<le;++i){
        tmp=tmp->down;
    }
    while(tmp->next!=nullptr){
        tmp=tmp->next;
    }
}
void SStable::Delete(node *t){
    node *de=t;
    node *tmp=t;
    while(tmp!=nullptr){
        de=tmp;
        tmp=tmp->succ;
        delete de;
    }
}

void SStable::putFileToLevel(node* li,int le){
    int size;
    unit *soc=new unit;//索引
    unit *flg;//索引标识
    node *tmp=li->succ;
    while(tmp!=nullptr){
        tmp=tmp->succ;
    }

    tmp=li->succ;;
    int n=1;//插入下一个文件的序号
    cell *pos;//插入下一个文件的位置
    pos=l(le,0);
    while(pos->next!=nullptr){
        if(pos->next->minkey>tmp->key) break;
        n++;
        pos=pos->next;
    }//寻找插入的第一个文件的序号和位置

    //准备插入
    fstream out;
    tmp=li;
    while(tmp!=nullptr){
       //该层文件数加一
        //生成新文件
        tmp=tmp->succ;
        if(tmp==nullptr) break;num[le]++;
        cell *ne = new cell;
        ne->minkey=tmp->key;


        size=0;
        if(num[le]!=n){
            //后续文件需要更名,数量为num【le】-n
            //cout<<num[le]-n<<endl;

            char **path;
            string newp;
            string bri;
            string oldp;
            path= new  char*[num[le]-n];
            cell *re=pos->next;
            for(int i=0;i<num[le]-n;++i){
               //取出地址
               if(re==nullptr){
                   exit(0);
               }
                re->path="./data/level"+to_string(le)+"/"+to_string(n+i+1)+".dat";

                
                re=re->next;
            }
            for(int i=num[le]-n;i>0;--i){
                newp="./data/level"+to_string(le)+"/"+to_string(n+i)+".dat";
                oldp="./data/level"+to_string(le)+"/"+to_string(n+i-1)+".dat";
                rename(oldp,newp);               
            }
            delete path;

        }
        string path="./data/level"+to_string(le)+"/"+to_string(n)+".dat";
        out.open(path,ios::binary|ios::out);
        if(!out){
            cout<<"open file error!"<<endl;
            exit(0);
        }
        flg=soc;
        while(tmp!=nullptr){
            flg->next=new unit(tmp->key,out.tellp());
            flg=flg->next;
            out.write((char*)&tmp->key,sizeof(uint64_t));
            out.write(tmp->value.c_str(),sizeof(char)*tmp->value.length());
            size+=sizeof(uint64_t)*2+sizeof(char)*tmp->value.length()+sizeof(int);
            ne->maxkey=tmp->key;
            
            if(size>(1<<21)-128) break;
            tmp=tmp->succ;
        }//插入键值对
        //生成新的插入文件单元信息到文件链表(pos后面)
        //ne->maxkey=tmp->key;
        ne->path=path;
        ne->socindex=out.tellp();
        
        
        //插入索引
        flg->next=new unit(0,out.tellp());
        flg=soc->next;
        while(flg!=nullptr){
            out.write((char*)&flg->key,sizeof(uint64_t));
            out.write((char*)&flg->pos,sizeof(int));
            flg=flg->next;
        }
        out.close();
        soc->Delete(soc);
        soc=new unit;//清空索引缓存

        //更新下一个文件序号和位置
        n++;
        ne->next=pos->next;
        pos->next=ne;
        
        pos=pos->next;
    }
   // showlist();
  //  cin>>i;

}

void SStable::deleteFilefromlevel(cell *f,int le){
        cell *flg=l(le,0);
        cell *del;
        string newp;
        int n=1;
        if(flg->next==nullptr){
            cout<<"no such file in this level!"<<endl;
            exit(0);
        }
        while(flg->next!=f){
            n++;
            flg=flg->next;
        }
        del=flg;
        flg=flg->next;
        remove(flg->path.c_str());
        while(flg->next!=nullptr){
            flg=flg->next;
            //更名
            newp="./data/level"+to_string(le)+"/"+to_string(n)+".dat";
            rename(flg->path.c_str(),newp.c_str());
            flg->path=newp;
            n++;
        }
        flg=del->next;
        del->next=flg->next;
        delete flg;
        num[le]--;
        

}

 void SStable::compact(int levelone,int leveltwo){
     if(num[levelone]<=(1<<(levelone+1))) return;
    uint64_t k;
    int p;
    char *v;
    node *newh=new node;//第一层需要归并的键值对链表
    node *tmpkv;
    node *del;
    unit *h=new unit;
    unit *tmp;
    fstream in;
    uint64_t maxkey,minkey;
    if(levelone==0){
        

        
       // unit *h=new unit;
        unit *tmp;
        node *he[3];
        node *ta[3];
        for(int i=0;i<3;++i){
            he[i]=new node;
            ta[i]=new node;
        }
        
        //读文件
        for(int i=0;i<3;++i){
        tmp=h;
        cell *ce=l(0,i+1);
        in.open(ce->path,ios::binary|ios::in);
        in.seekg(ce->socindex,ios::beg);
        if(!in){
            cout<<"Error!1"<<endl;
            exit(0);
        }
        while(in.read((char*)&k,sizeof(uint64_t))&&in.read((char*)&p,sizeof(int))){
            tmp->next=new unit(k,p);
            tmp=tmp->next;  //读索引到h
        }
        in.close();
        tmp=h->next;
        tmpkv=he[i];
        in.open(ce->path);
        while(tmp->next!=nullptr){
            v=new char[tmp->next->pos-tmp->pos-7];
            v[tmp->next->pos-tmp->pos-8]='\0';
            in.seekg(tmp->pos+8,ios::beg);
            in.read(v,sizeof(char)*(tmp->next->pos-tmp->pos-8));
            tmpkv->succ=new node(tmp->key,v);
            tmpkv=tmpkv->succ;
            tmp=tmp->next;
        
            delete v;
        }
        in.close();
        tmpkv->succ= ta[i];
      //  ta[i]=tmpkv->succ;
        
        }
        deleteFilefromlevel(l(0,1),0);
        deleteFilefromlevel(l(0,1),0);
        deleteFilefromlevel(l(0,1),0);//删除文件
        h->Delete(h); //释放索引缓存
        
        //tmpkv=newh;
        
        node *flg1=he[0]->succ,*flg2=he[1]->succ,*flg3=he[2]->succ;
        node *box=new node;
        tmpkv=box;
        while(flg1!=ta[0]||flg2!=ta[1]){
            while(flg1!=ta[0]&&(flg2==ta[1]||flg1->key<flg2->key)){
                del=flg1;
                tmpkv->succ=new node(flg1->key,flg1->value);
                tmpkv=tmpkv->succ;
                flg1=flg1->succ;
                delete del;
            }
            while(flg2!=ta[1]&&(flg1==ta[0]||flg2->key<flg1->key)){
                del=flg2;
                tmpkv->succ=new node(flg2->key,flg2->value);
                tmpkv=tmpkv->succ;
                flg2=flg2->succ;
                delete del;
            }
            if(flg1!=ta[0]&&flg2!=ta[1]&&flg1->key==flg2->key){
                tmpkv->succ=new node(flg2->key,flg2->value);
                tmpkv=tmpkv->succ;
                del =flg1;
                flg1=flg1->succ;
                delete del;
                del=flg2;
                flg2=flg2->succ;
                delete del;
            }

        }
        flg1=box->succ;
        tmpkv=newh;
        while(flg1!=nullptr ||flg3!=ta[2]){
            while(flg1!=nullptr&&(flg3==ta[2]||flg1->key<flg3->key)){
                del=flg1;
                tmpkv->succ=new node(flg1->key,flg1->value);
                tmpkv=tmpkv->succ;
                flg1=flg1->succ;
                delete del;
            }
            while(flg3!=ta[2]&&(flg1==nullptr||flg3->key<flg1->key)){
                del=flg3;
                tmpkv->succ=new node(flg3->key,flg3->value);
                tmpkv=tmpkv->succ;
                flg3=flg3->succ;
                delete del;
            }
            if(flg1!=nullptr&&flg3!=ta[2]&&flg1->key==flg3->key){
                tmpkv->succ=new node(flg3->key,flg3->value);
                tmpkv=tmpkv->succ;
                del =flg1;
                flg1=flg1->succ;
                delete del;
                del=flg3;
                flg3=flg3->succ;
                delete del;
            }

        }
        
        maxkey=tmpkv->key;
        minkey=newh->succ->key;//取出新单元的范围
        tmpkv=newh->succ;
    }else{
        //levelone不为0
       //需要合并的个数
        
        cell *ce=l(levelone,(1<<(levelone+1))+1);//第一个需要合并的文件
       // cout<<"层1第一个需要合并的文件"<<ce->path<<"!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        minkey=ce->minkey;//取出范围

        tmpkv=newh;
        while(ce!=nullptr){            
        tmp=h; 
        in.open(ce->path,ios::binary|ios::in);
        in.seekg(ce->socindex,ios::beg);
        while(in.read((char*)&k,sizeof(uint64_t))&&in.read((char*)&p,sizeof(int))){
            
            tmp->next=new unit(k,p);
            tmp=tmp->next;  //读索引到h
            if(k!=0) maxkey=k;
        }
        
        //取出范围
        in.close();
        tmp=h->next;
        uint64_t k;
        
        in.open(ce->path,ios::binary|ios::in);
        while(tmp->next!=nullptr){
            v=new char[tmp->next->pos-tmp->pos-7];
            v[tmp->next->pos-tmp->pos-8]='\0';
            in.seekg(tmp->pos,ios::beg);
            in.read((char*)&k,sizeof(uint64_t));
            in.read(v,sizeof(char)*(tmp->next->pos-tmp->pos-8));
            tmpkv->succ=new node(tmp->key,v);
            tmpkv=tmpkv->succ;
            tmp=tmp->next;
            delete v;
        } 
        in.close();
        h->Delete(h);//释放索引缓存
        h=new unit;
        ce=ce->next;
        }
        ce=l(levelone,(1<<(levelone+1))+1);
        while(ce!=nullptr){
            deleteFilefromlevel(ce,levelone);
            ce=l(levelone,(1<<(levelone+1))+1);

        }
        
    }//if层1为0层
    
    cell *Union;
    int n=0;
    cell *flg;
    cell *sig;
    node *newh2=new node;//第二层需要归并的链表
    node *li;//归并newh和newh2
    sig=l(levelone,0);//若第二层为空创建第二层，层数++
    
    if(sig->down==nullptr) {
        sig->down=new cell;
        level++;    
        string path="./data/level"+to_string(leveltwo);
        create_directory(path.c_str());
    }
    
    int index=0;
    sig=l(leveltwo,0)->next;
    flg=l(leveltwo,0);
    if(sig!=nullptr){ //第二层有文件时
   // cout<<minkey<<'\t'<<maxkey<<"!!!!!!!!!!!!!!!!!!!!!!"<<endl;
    li=new node;
        while(sig!=nullptr){
        if(sig->maxkey>=minkey&&sig->minkey<=maxkey){
            n++;
        }
        else{
            if(n==0) {
                flg=sig;
                index++;}
        }
        sig=sig->next;
        }//找到有交集文件



        
        Union=flg;
        tmpkv=newh2;
        for(int i=0;i<n;++i){
            Union=Union->next;
            //cout<<"归并："<<Union->path<<endl;
            h=new unit;
            tmp=h;
            in.open(Union->path,ios::binary|ios::in);
            in.seekg(Union->socindex,ios::beg);
            if(!in){
                cout<<"Error"<<endl;
                exit(0);
                }
            while(in.read((char*)&k,sizeof(uint64_t))&&in.read((char*)&p,sizeof(int))){
                tmp->next=new unit(k,p);
                tmp=tmp->next;  //读索引到h
               // cout<<"socket:"<<tmp->key<<'\t'<<tmp->pos<<endl;
                }
            in.close();
            tmp=h->next;
            in.open(Union->path);
            if(!in){
                cout<<"open file error!"<<endl;
                exit(0);
                }
            while(tmp->next!=nullptr){
                v=new char[tmp->next->pos-tmp->pos-7];
                v[tmp->next->pos-tmp->pos-8]='\0';
                in.seekg(tmp->pos+8,ios::beg);
                in.read(v,sizeof(char)*(tmp->next->pos-tmp->pos-8));
                tmpkv->succ=new node(tmp->key,v);
                tmpkv=tmpkv->succ;
            
                tmp=tmp->next;
                delete v;
                }//读到newh2
            in.close();
            h->Delete(h);
            // tmpkv=newh2;
            // for(int i=0;;i++){
            //     if(tmpkv==nullptr) break;
            //     tmpkv=tmpkv->succ;
            //     }
            }
        //和newh归并
        node *tmp1=newh->succ;
        node *tmp2=newh2->succ;
        node *tmp3=li;
        while(tmp1!=nullptr||tmp2!=nullptr){
            while(tmp1!=nullptr&&(tmp2==nullptr||tmp1->key<tmp2->key)){
                tmp3->succ=new node(tmp1->key,tmp1->value);
                tmp3=tmp3->succ;
                del=tmp1;
                tmp1=tmp1->succ;
                delete del;
            }
            while(tmp2!=nullptr&&(tmp1==nullptr||tmp2->key<tmp1->key)){
                tmp3->succ=new node(tmp2->key,tmp2->value);
                tmp3=tmp3->succ;
                del=tmp2;
                tmp2=tmp2->succ;
                delete del;
            }
            while(tmp1!=nullptr&&tmp2!=nullptr&&(tmp1->key==tmp2->key)){
                //if(tmp1->value!=""){
                    tmp3->succ=new node(tmp1->key,tmp1->value);
                tmp3=tmp3->succ;
                //}
                del=tmp1;
                tmp1=tmp1->succ;
                delete del;
                del=tmp2;
                tmp2=tmp2->succ;
                delete del;
            }
        }
        //删除第二层文件
        for(int i=0;i<n;++i){
            deleteFilefromlevel(l(leveltwo,index+1),leveltwo);
            
        }
    }
    else{
        //第二层无文件时
        li=newh;
    }

    putFileToLevel(li,leveltwo);
    
    compacttime++;
    if(num[leveltwo]>(1<<(leveltwo+1)))compact(leveltwo,leveltwo+1) ;//compact下一层


 }

void SStable::putFile(node *h,node *t,int le){
    create_directory("./data/cache");
    string path="./data/level"+to_string(le);
    create_directory("./data");
    create_directory(path.c_str());
   
    path+="/"+to_string(++num[le])+".dat";
    fstream out(path.c_str(),ios::binary|ios::out);
    if(!out){
        cout<<"Error file out"<<endl;
        exit(0);
    }
    node *tmp=h->succ;
    unit *u=new unit;//索引
    unit *nex=u;
    string input;
    while(tmp!=t){
        nex->next=new unit(tmp->key,out.tellp());
        out.write((char*)&(tmp->key),sizeof(tmp->key));
        nex=nex->next;
        input=tmp->value+"a";
        out.write(tmp->value.c_str(),sizeof(char)*tmp->value.length());
        tmp=tmp->succ;
    }
    nex->next=new unit(0,out.tellp());
    int index=out.tellp();
    nex=u->next;
    while(nex!=nullptr){
        out.write((char*)&nex->key,sizeof(uint64_t));
        out.write((char*)&nex->pos,sizeof(int));
        nex=nex->next;
    }
    out.close();
    cell *tm=head;
    for(int i=0;i<num[le]-1;++i){
        tm=tm->next;
    }
    
    tm->next=new cell;
    tm=tm->next;
    tm->socindex=index;
    tm->minkey=h->succ->key;
    tm->maxkey=t->pred->key;
    tm->path=path;

    u->Delete(u);


    clock_t start=clock();
    if(num[le]>(1<<(le+1))) compact(le,le+1);  
    clock_t end = clock();
    CT+=end-start;
    updatecache(); 
    return;
}
void SStable::updatecache(){
   // remove("./data/cache/cache.dat");
    //create_directory("./data/cache/cache.dat");
    fstream out;
    out.open("./data/cache/cache.dat",ios::out|ios::binary);
    out.write((char*)&level,sizeof(int));//写入层数
    for(int i=0;i<=level;++i){
        out.write((char*)&num[i],sizeof(int));
        cell *tmp=l(i,0)->next;
        for(int m=0;m<num[i];++m){
            //out.write(tmp->path.c_str(),sizeof(char)*tmp->path.length());
            out.write((char*)&tmp->socindex,sizeof(int));
            out.write((char*)&tmp->minkey,sizeof(uint64_t));
            out.write((char*)&tmp->maxkey,sizeof(uint64_t));
            tmp=tmp->next;
        }
    }
    out.close();

}

void SStable::readcache(){
    fstream in;
    in.open("./data/cache/cache.dat");
    if(!in) {
        return;
    }
    delete num;
    num = new int [10000];
    int n;
    int nn;
    uint64_t min;
    uint64_t max;
    int soc;
    cell *flg=head;
    cell *tmp;
    
    in.seekg(ios::beg);
    in.read ((char*)&n,sizeof(int));
    this->level=n;
    for(int i=0;i<=n;++i){
        tmp=flg;
        in.read((char*)&nn,sizeof(int));
        this->num[i]=nn;
        for(int m=0;m<nn;++m){
            tmp->next=new cell;
            tmp=tmp->next;
            tmp->path="./data/level"+to_string(i)+"/"+to_string(m+1)+".dat";
            in.read((char*)&soc,sizeof(int));
            in.read((char*)&min,sizeof(uint64_t));
            in.read((char*)&max,sizeof(uint64_t));
            tmp->socindex=soc;
            tmp->minkey=min;
            tmp->maxkey=max;
        }
        if(i!=n)flg->down=new cell;
        flg=flg->down;
    }
    in.close();
}

void SStable::Remove(){
    string path;
    for(int i=0;;++i){
        path="./data/level"+to_string(i);
        if(!remove_all(path.c_str())) break;
        level=0;
    }
    remove("./data/cache/cache.dat");
    head=new cell();
    level=0;
    delete num;
    num = new int[10000];

}
SStable::SStable(){
    head=new cell;
    level=0;
    compacttime=0;
    CT=0;
    num=new int[10000];
    readcache();
}
SStable::~SStable(){
    string path;
    for(int i=0;i<=level;++i){
        path="./data/level"+to_string(level);
        remove_all(path.c_str());
    }
    delete num;
    delete head;
}