#include <iostream>
#include "Bloom.h"
#include <cmath>
#include <cstdlib>
using namespace std;


int main()
{
    /**
     随机生成10万组整形（0-1000万）数据作为插入，每次插入2000，每插入一次，生成40万组数据（1000万-20000万）检测假阳性率，忽略重复
     */
    srand( int(time(nullptr)));
    unsigned int Hash1(unsigned  int,unsigned int);
    unsigned int Hash2(unsigned int,unsigned int);
    unsigned int Hash3(unsigned int,unsigned int);
    unsigned int Hash4(unsigned int,unsigned int);
    bloom *b1,*b2,*b3;
    unsigned int insert;
    unsigned int check;
    cout<<RAND_MAX<<endl;
    b1=new bloom(100000,200000,2);
    b2=new bloom(100000,200000,2);
    b3=new bloom(200000,400000,4);
    for( int i =0;i<200000;++i){
        insert=unsigned( double(rand())/double(RAND_MAX)*double(1000000));
        b3->insert(Hash1(insert,400000),Hash2(insert,400000),Hash3(insert,400000),Hash4(insert,400000));
        if(i%2==1){
            insert=unsigned ( double(rand())/double(RAND_MAX)*double(1000000));
            b1->insert(Hash1(insert,200000),Hash2(insert,200000));
            b2->insert(Hash3(insert,200000),Hash4(insert,200000));
        }
        if(i%4000==3999){
            unsigned int error1,error2;
            error1=error2=0;
            for( int m=0;m<400000;++m){
                check=unsigned (double(rand())/double(RAND_MAX)*double(1000000)+1000000);
                if(b1->check(Hash1(check,200000),Hash2(check,200000))==true&&b2->check(Hash3(check,200000),Hash4(check,200000))==true) error1++;
                if(b3->check(Hash1(check,400000),Hash2(check,400000),Hash3(check,400000),Hash4(check,400000))==true) error2++;
            }
            cout<<"m/n: "<<(400000/i)<<"    Wrong Rate 1: "<<double(error1)/200000<<"   Wrong Rate 2 : "<<double(error2)/400000<<endl;

        }
    }



    return 0;
}
unsigned int Hash1(unsigned int x,unsigned int m){
      x = ~x + (x << 15); // x = (x << 15) - x - 1;
    x = x ^ (x >> 12);
    x = x + (x << 2);
    x = x ^ (x >> 4);
    x = x * 2057; // x = (x + (x << 3)) + (x << 11);
    x = x ^ (x >> 16);
    return x%m;

}
unsigned int Hash2(unsigned int x,unsigned int m){
    x = (~x) + (x << 21); // x = (x << 21) - x - 1;
    x = x ^ (x >> 24);
    x = (x + (x << 3)) + (x << 8); // x * 265
    x = x ^ (x >> 14);
    x = (x + (x << 2)) + (x << 4); // x * 21
    x = x ^ (x >> 28);
    x = x + (x << 31);
    return x%m;

}
unsigned int Hash3(unsigned int x,unsigned int m){
    x = (x+0x7ed55d16) + (x<<12);
    x = (x^0xc761c23c) ^ (x>>19);
    x = (x+0x165667b1) + (x<<5);
    x = (x+0xd3a2646c) ^ (x<<9);
    x =(x+0xfd7046c5) + (x<<3); // <<和 +的组合是可逆的
    x = (x^0xb55a4f09) ^ (x>>16);
    return x%m;
}
unsigned int Hash4(unsigned int x,unsigned int m){
    x = (x+0xfd7046c5) + (x<<3);  // <<和+ 是可逆
    x = (x+0xfd7046c5) + (x>>3);  // >>和+ 不保证是可逆的
    x = (x^0xb55a4f09) ^ (x<<16); // ^ 和<< 是可逆
    x = (x^0xb55a4f09) ^ (x>>16);
    return x%m;
}
