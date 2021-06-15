#include "Bloom.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
bloom::bloom(unsigned int n,unsigned int m,unsigned int k){
    this->n=n;
    this->m=m;
    this->k=k;
    M = new bool[m]();
    return;
}

void bloom::insert(unsigned int a,unsigned int b ){
    M[a]=1;
    M[b]=1;
    return;
}

bool bloom::check(unsigned int a, unsigned int b){
    if(M[a]==1&&M[b]==1) return true;
    else return false;
}
void bloom::insert(unsigned int a, unsigned int b, unsigned int c, unsigned int d){
    M[a]=1;
    M[b]=1;
    M[c]=1;
    M[d]=1;
    return;
}
bool bloom::check(unsigned int a, unsigned int b, unsigned int c, unsigned int d){
    if(M[a]==1&&M[b]==1&&M[c]==1&&M[d]==1) return true;
    else return false;
}
bloom::bloom(){

}

bloom::~bloom(){
    delete M;
}
