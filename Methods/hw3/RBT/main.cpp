#include <iostream>
#include "rbt.h"
#include "cmath"
#include "cstdlib"
#include <ctime>

using namespace std;
bool existinbuf(int k,int *a,int poin){
    for(int i=0;i<poin;++i){
        if(a[poin]==k) return true;
    }
    return false;
}

int main()
{
    srand(unsigned (time(0)));
    int n;
    RBT *tree;

    int *insert;
    //随机数0-2000多万；
    cout<<"序号 "<<"\t插入时间 "<<"\t双红修正次数  "<<endl;
    n=10000;
    cout<<"节点数："<<n<<endl;
    for(int i =0;i<10;++i){//取十次样本
        insert = new int [n/100];
        tree= new RBT;
        for(int j=0;j<n;++j){
            while(tree->getN()!=n) tree->insert(rand());//建树
        }
        int  in;
        int poin=0;
        for(int m=0;m<n/100;++m){
           in=rand();
            if(!tree->exist(in)&&!existinbuf(in,insert,poin)) {
                insert[poin]=in;
                poin++;
            }
        }
        clock_t  starttime=clock();
        int RRN=tree->getRRN();//初始红修正次数
        for(int j=0;j<n/100;++j){
            tree->insert(insert[j]);
        }
        clock_t endtime = clock();
        double time=((double)(endtime-starttime))/1000;
        cout<<i<<"\t"<<time<<"ms\t"<<tree->getRRN()-RRN<<endl;
        delete  tree;
    }

    n=100000;
    cout<<"节点数："<<n<<endl;
    for(int i =0;i<10;++i){//取十次样本
        insert = new int [n/100];
        tree= new RBT;
        for(int j=0;j<n;++j){
            while(tree->getN()!=n) tree->insert(rand());//建树
        }
        int  in;
        int poin=0;
        for(int m=0;m<n/100;++m){
           in=rand();
            if(!tree->exist(in)&&!existinbuf(in,insert,poin)) {
                insert[poin]=in;
                poin++;
            }
        }
        clock_t  starttime=clock();
        int RRN=tree->getRRN();//初始红修正次数
        for(int j=0;j<n/100;++j){
            tree->insert(insert[j]);
        }
        clock_t endtime = clock();

        double time=((double)(endtime-starttime))/1000;
        cout<<i<<"\t"<<time<<"ms\t"<<tree->getRRN()-RRN<<endl;
        delete  tree;
    }
    n=1000000;
    cout<<"节点数："<<n<<endl;
    for(int i =0;i<10;++i){//取十次样本
        insert = new int [n/100];
        tree= new RBT;
        for(int j=0;j<n;++j){
            while(tree->getN()!=n) tree->insert(rand());//建树
        }
        int  in;
        int poin=0;
        for(int m=0;m<n/100;++m){
           in=rand();
            if(!tree->exist(in)&&!existinbuf(in,insert,poin)) {
                insert[poin]=in;
                poin++;
            }
        }

        int RRN=tree->getRRN();//初始红修正次数
        clock_t  starttime=clock();
        for(int j=0;j<n/100;++j){
            tree->insert(insert[j]);
        }
        clock_t endtime = clock();
        double time=((double)(endtime-starttime))/1000;//CLOCKS_PER_SEC为1000时单位是s，为1000000时单位是ms
        cout<<i<<"\t"<<time<<"ms\t"<<tree->getRRN()-RRN<<endl;
        delete  tree;
}
//    cout<<"??????"<<endl;
//    int n;
//    int t;
//    cin>>n;
//    while(n){
//        cin>>t;
//        tree.insert(t);
//        n--;
//    }

    return 0;
}
