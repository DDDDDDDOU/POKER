#include "rbt.h"
#include <iostream>
using namespace std;

RBT::RBT()
{
    Rnum = 0;
    Bnum = 0;
    Nnum = 0;
    bheight=0;
    root =  nullptr;
}

RBT::node::node(int k,color c){
    key  =  k;
    left   =  nullptr;
    right =  nullptr;
    height=1;
    co    =  c;
}

RBT::node* RBT::father(node *t){
    if (t==root) return nullptr;
    node *tmp = root ;
    while(tmp){
        if(tmp->left==t||tmp->right==t) break;
        else tmp = t->key>tmp->key ? tmp->right :tmp->left;
    }
    return tmp;
}
bool RBT::exist(int k){
    node *tmp=root;
    while(tmp!=nullptr){
        if(k==tmp->key) return true;
        if(k<tmp->key){ tmp=tmp->left;
        continue;}
        if(k>tmp->key) {
            tmp=tmp->right;
        continue;}
    }
     return false;

}

void RBT::insert( int k ) {

    if(root==nullptr) {
        root = new node(k,Black);
        bheight++;
        Bnum++;
    }

    else{
        node *ne;
        node *fa;
        ne=fa=root;
        if(fa->key==k){
      //      cout<<"has exsited"<<endl;
            return;
        }
        ne = (root->key>k) ? ne->left : ne->right;

        while(ne!=nullptr){
            fa = ne ;
            if(fa->key==k) {
       //         cout<<"has exsited" <<endl;
                return;
            }
            ne= (k>ne->key) ? ne->right : ne->left;
        }
        if(k<fa->key) { fa->left = new node(k,Red); Rnum++;ne=fa->left; }
        else { fa ->right = new node(k,Red);Rnum++; ne=fa->right; }  //插入红色新节点
   //     cout<<ne->key<<endl;
        //fa 是父亲 ne是新节点
    //    cout<<ne->key;
        rebanlance(ne); // 调整子节点

    }
    Nnum++; //节点数++
//    cout<<Rnum<<'\t'<<Bnum<<endl;
//    cout<<"root :  "<<root->key<<endl;

    return;

}

void RBT::rebanlance(node *t){
    node *fa = father(t);
 //   cout<<"fataher :  " <<fa->key<<endl;
   // cout<<"bb"<<fa->key<<endl;
    if(fa->co==Black) return;//父亲节点是黑色 直接返回
  //  node *ne = t; //儿子
    node *gr = father(fa);    //父亲节点为红，此时i祖父节点一定在
    rrnum++;//双红调整次数加一
    node *un = gr->left==fa ? gr->right : gr->left; //叔叔节点 或不存在 或为黑，或为红
    if(un&&un->co==Red){
//            if(gr->left==fa &&fa->right==ne) {
//                //左右叔叔
//                RRrotate(fa);
//                fa=gr->left;
//                ne= fa->left;
//            }
//            if(gr->right==fa &&fa->left==ne){
//                //右左叔叔
//                LLrotate(fa);
//                fa=gr->right;
//                ne = fa->right;
//            }
            //变色
            fa->co=Black; un->co=Black;
            gr->co = Red;
            Rnum--;
            Bnum++;
            if(gr==root) {
                gr->co=Black;
                Bnum++;
                Rnum--;   //看根节点是不是红色 转为黑色
                bheight++;
                return;
            }
            rebanlance(gr); //父节点作为新节点
            return;


    }//叔叔节点存在
    else if(!un || un->co==Black){
       if(gr->left==fa){
            if(fa->left == t){
              //  cout<<"a"<<endl;
                setcolor(gr,Red);
                setcolor(fa,Black);
                LLrotate(gr);
                return;
            }
            if(fa->right==t){
                RRrotate(fa);
             //   cout <<"fa: "<<fa->key<<endl;
                rebanlance(fa);
                return;
            }
       }
       if(gr->right==fa){
           if(fa->right==t){
               setcolor(gr,Red);
               setcolor(fa,Black);
               RRrotate(gr);
               return;
           }
           if(fa->left==t){
               LLrotate(fa);
               rebanlance(fa);
               return;
                }
           }
    }//叔叔节点不存在



}



void RBT::setcolor(node *t, color c){
    t->co = c;
}

void RBT::LLrotate(node *t){
    if(t==root){
        node *r = t->left;
        t->left=r->right;
        r->right=t;
        root =r;
        return;
    }
    node *fa;
    fa = father(t);
    if(fa->left==t) fa->left=t->left; else fa->right=t->left;
    node *son = t->left;
    t->left = son->right==nullptr ? nullptr : son->right;
    son->right =t;
}


void RBT::RRrotate(node *t){
    if(t==root){
        node *r = t->right;
        t->right=r->left;
        r->left=t;
        root=r;
        return;
    }
    node *fa;
    fa = father(t);
    if(fa->left==t) fa->left = t->right ; else fa->right = t->right;
    node *son = t->right;
    t->right = son->left==nullptr ? nullptr : son->left;
    son->left = t;
}

void RBT::LRrotate(node *t){
    RRrotate(t->left);
    LLrotate(t);
}
void RBT::RLrotate(node *t){
    LLrotate(t->right);
    RRrotate(t);
}

int RBT::height(node *t){
    if(!t) return 0;
    t->height= max(height(t->left),height(t->right))+1;
    return t->height;
}
int RBT::getB(){
    return Bnum;
}

int RBT::getR(){
    return Rnum;
}

int RBT::getN(){
    return Nnum;
}

int RBT::getH(){
    return height(root);
}

int RBT::getRRN(){
    return rrnum;
}
int RBT::getBH(){
    return bheight;
}
bool RBT::isblack(node *t){
    return t->co==Black;
}

RBT::~RBT(){
    delete root;
}


