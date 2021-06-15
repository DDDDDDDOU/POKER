#include "grap.h"
#include <fstream>
#include <iostream>
using namespace std;
graph::graph(){
    fstream in("./data.in",ios::in);
    in>>n;
    in>>E;
    int v,u,value;
    table = new int*[n];
    time  = new int*[n];
    for(int i=0;i<n;++i) {
        table[i]=new int[n];
        time[i] =new int[2];    
        
    }
    for(int i=0;i<n;++i){
        for(int m=0;m<n;++m){
           table[i][m]=0;
        }
    }
    for(int i=0;i<E;++i) {
        in>>v;
        in>>u;
        in>>value;
        table[v][u]=value;
    }
    in.close();
//创建邻接表，初始化开始时间表

    U=new int[n];//子集
    numU=0;


}

bool graph::inU(int i){
    for(int m=0;m<numU;++m){
        if(U[m]==i) return true;
    }
    return false;
}

void graph::findway(int start,int end){
    this->start=start;
    this->end=end;
    time[start][0]=0;//开始节点的最早开始时间为0
    ebway(start);  //计算各店最早开始时间.
   time[end][1]=time[end][0];//设置终点的最晚开始时间等于最早开始时间
    numU=0;
    delete U;
    U = new int[n];//清空U
   lbway(end);//计算各点最晚开始时间
    output();//输出路径

}

struct node
{
    int i;
    int l;
    node(){
        i=100;l=100000000;
    }
        /* data */
};

bool compare(node a,node b){
    return a.l<b.l;
}

void graph::output(){
    node *a;
    a=new node[n];
    int num=0;
    for(int i=0;i<n;++i){
        if(time[i][0]==time[i][1]) {
            a[num].i=i;
            a[num].l=time[i][0];
            num++;
            }
    }
    sort(a,a+n,compare);
    cout<<"最短路径："<<endl;
    for(int i=0;i<num;++i){
        cout<<a[i].i<<'\t';
    }
    cout<<endl;
}

void graph::lbway(int v){
    U[numU]=v;
    numU++;
    for(int i=0;i<n;++i){
        if(inU(i)) continue;//如果点在U里面，寻找下一个点

        //当i不在U里面时，判断其子节点是否全在U，若全在，则计算其最晚开始时间并加入U，否则过滤；
        bool flag=true;//若子节点全在U，记为true；
        for(int m=0;m<n;++m){
            if(table[i][m]==0) continue;//两点间无边
            if(!inU(m)) {
                flag=false;//不全在U，直接退出，找下个点
                break;
            }
        }
        if(flag==false) continue;
        for(int m=0;m<n;++m){
            if(table[i][m]==0) continue;//两点间无边
            if(time[i][1]==0) time[i][1]=time[m][1]-table[i][m];
            else if((time[m][1]-table[i][m])<time[i][1]) time[i][1]=time[m][1]-table[i][m];//更新该点最晚开始时间
        }
        lbway(i);//将该点插入U，结束函数
        return;
    }
}

void graph::ebway(int v){//设置各点最早开始时间
    U[numU]=v;
    numU++;
                        //将该点放入子集U中，设置起点最早开始时间等于最晚开始时间等于0
    for(int i=0;i<n;++i){
        if(inU(i)) continue;//如果点在U里面，寻找下一个点

        //当i不在U里面时，判断其父节点是否全在U，若全在，则计算其最大路径并加入U，否则过滤；
        bool flag=true;//若父节点全在U，记为true；
        for(int m=0;m<n;++m){
            if(table[m][i]==0) continue;//两点间无边
            if(!inU(m)) {
                flag=false;//不全在U，直接退出，找下个点
                break;
            }
        }
        if(flag==false) continue;
        for(int m=0;m<n;++m){
            if(table[m][i]==0) continue;//两点间无边
            if((time[m][0]+table[m][i])>time[i][0]) time[i][0]=time[m][0]+table[m][i];//更新该点最早开始时间
        }
        ebway(i);//将该点插入U，结束函数
        return;
    }
    

}