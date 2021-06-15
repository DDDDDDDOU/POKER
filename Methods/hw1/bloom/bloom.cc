#include "bloom.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
bloom::bloom(int n,int m,int k){
    srand(int (time(NULL)));
    this->n=n;
    this->m=m;
    this->k=k;
    M = new bool[m]();
    for(int i = 0; i <m;++i){
        cout<<M[i];
    }
}

void bloom::insert(int n,int (*h1)(int x),int (*h2)(int y) ){
 return;
}

int bloom::check(int N){
    return 0;
}
bloom::bloom(){
    
}