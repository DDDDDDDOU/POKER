#ifndef Bloom_H
#define Bloom_H


class bloom{
private:
    int k;           //k Hash function
    int m;           //m bite list
    int n;           //inpu n data
    bool *M;


    



public:
    bloom();
    bloom(int n,int m, int k);
    void insert(int n,int (*h1)(int x),int (*h2)(int y) );
    int check(int N);

};

#endif