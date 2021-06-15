#ifndef LS_H
#define LS_H
 #include <ctime> 
#include <iostream>   
using namespace std;   
   
void Swap(int &x,int &y);  
  
inline int Random(int x, int y);  
  
void BubbleSort(int a[],int p,int r);  
  
int Partition(int a[],int p,int r,int x);  
  
int Select(int a[],int p,int r,int k);  
  

  
void Swap(int &x,int &y)  
{  
    int temp = x;  
    x = y;  
    y = temp;  
}  
  
inline int Random(int x, int y)  
{  
     int ran_num = rand() % (y - x) + x;  
     return ran_num;  
}  
  
//冒泡排序  
void BubbleSort(int a[],int p,int r)  
{  
     //记录一次遍历中是否有元素的交换     
     bool exchange;    
     for(int i=p; i<r;i++)    
     {    
        exchange = false ;    
        for(int j=0; j<=r-i; j++)    
        {    
            if(a[j]<a[j-1])    
            {    
                Swap(a[j],a[j-1]);   
                exchange = true;    
            }     
        }     
        //如果这次遍历没有元素的交换,那么排序结束     
        if(false == exchange)    
        {  
             break ;    
        }  
     }  
}  

int Partition(int a[],int p,int r,int x)  //快速排序一趟划分
{  
    int i = p-1,j = r + 1;  
  
    while(true)  
    {  
        while(a[++i]<x && i<r);  
        while(a[--j]>x);  
        if(i>=j)  
        {  
            break;  
        }  
        Swap(a[i],a[j]);  
    }     
    return j;  
}  
  
  
int Select(int a[],int p,int r,int k)  
{  
    if(r-p<75)  
    {  
        BubbleSort(a,p,r);  
        return a[p+k-1];  
    }  
    //(r-p-4)相当于n-5  
    for(int i=0; i<=(r-p-4)/5; i++)  
    {  
        //每五个一组 
        BubbleSort(a,p+5*i,p+5*i+4);  
        Swap(a[p+5*i+2],a[p+i]);  
    }  
    //找中位数的中位数  
    int x = Select(a,p,p+(r-p-4)/5,(r-p-4)/10);  
    int i = Partition(a,p,r,x);  
    int j = i-p+1;  
    if(k<=j)  //看是否是要找的数，否则递归
    {  
        return Select(a,p,i,k);  
    }  
    else  
    {  
        return Select(a,i+1,r,k-j);  
    }  
}


void exchange(int * a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
void print_arr(int *a, int size) //打印函数 
{
  cout << "打印数组：";
  for (int i = 0; i<size; i++)  //打印数组 
  {
    cout << a[i] << " ";
  }
  cout << endl << endl;
}

/*序列划分函数*/
int partition(int a[], int p, int r) {
  int key = a[r];//取最后一个
  int i = p - 1;
  for (int j = p; j < r; j++)
  { 
    if (a[j] <= key)
    {     
      i++;
      //i一直代表小于key元素的最后一个索引，当发现有比key小的a[j]时候，i+1 后交换     
      exchange(&a[i], &a[j]);
    }   
  } 
  exchange(&a[i + 1], &a[r]);//将key切换到中间来，左边是小于key的，右边是大于key的值。
  return i + 1;
}
  
void quickSort(int a[], int p, int r) {
  int position = 0;
  if (p<r)
  {
    position = partition(a,p,r);//返回划分元素的最终位置
    quickSort(a,p,position-1);//划分左边递归
    quickSort(a, position + 1,r);//划分右边递归
  } 
}

#endif //
