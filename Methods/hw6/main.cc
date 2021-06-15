#include <iostream>
using namespace std;
#include "linerselect.h"
#include <cstdlib>

#define max 1000000
int main(){

    clock_t start,end;
       //初始化数组  
    int *a;  
    int *b;
    a=new int [max];
    b=new int [max];
    int s;
    int tmp;
  
    //必须放在循环体外面  
    srand((unsigned)time(0));  
  
    for(int i=0; i<max; i++)  
    {  
        tmp = Random(0,20000000);  
        a[i]=tmp;
        b[i]=tmp;
        // cout<<i<<":"<<b[i]<<endl;
    }  
    cout<<endl; 
    
    start = clock();
    s=Select(a,0,max-1,23);
    end=clock();
    // for(int i=0;i<max;++i) cout<<"a["<<i<<"]:"<<a[i]<<'\t';
    cout<<endl;
    cout<<"第23小元素是"<<s<<endl;  
    cout<<"liner运行时间："<<end-start<<endl;
  

    //重新排序，对比结果  
    start=clock();
    quickSort(b,0,max-1);  
    end=clock();
        // for(int i=0;i<max;++i) cout<<"b["<<i<<"]:"<<b[i]<<'\t';
    cout<<endl;
    cout<<"第23小元素是"<<b[22]<<endl;  
    cout<<"快排运行时间："<<end-start<<endl;


    // cout <<endl<<endl;
    // int ass[]={4,2,6,14,78,1434,13,6,1,0,12,1115,53453,14124,13213,66666,88575,234,131231,1};
    // quickSort(ass,0,15);
    // for(int i=0;i<16;++i){
    //     cout<<ass[i];
    //     cout<<'\t';
    // }

}