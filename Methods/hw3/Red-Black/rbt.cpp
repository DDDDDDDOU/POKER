#include "rbt.h"
#include <iostream>
using namespace std;

RBT::RBT()
{
    Rnum = 0;
    Bnum = 0;
    root =  nullptr;
}

RBT::node::node(int k,color c){
    key  =  k;
    left   =  nullptr;
    right =  nullptr;
    co    =  c;
}

RBT::node* RBT::father(node *t){
    if (t==root) return nullptr;
    node *tmp = root ;
    while(tmp){
        if(tmp->left==t||tmp->right==t) return tmp;
        else tmp = t->key>tmp->key ? tmp->right :tmp->left;
    }
    return tmp;
}

void RBT::insert( int k ) {
    if(root==nullptr) root = new node(k,Red);
    else{
        node *tmp=root;
        tmp = (root->key>k) ? tmp->left : tmp->right;
        node *pre = root;
        while(tmp!=nullptr){
            pre = tmp ;
            tmp= (k>tmp->key) ? tmp->right : tmp->left;
        }
        if(k<pre->key) { pre->left = new node(k,Red); cout<<pre->left->key<<"inserted"<<endl; }
        else { pre ->right = new node(k,Red); cout<<pre->right->key<<"inserted"<<endl; }
    }  //插入红色新节点




}


RBT::~RBT(){
    
}









