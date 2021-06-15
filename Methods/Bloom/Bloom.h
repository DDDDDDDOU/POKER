#ifndef BLOOM_H
#define BLOOM_H


class bloom{
private:
    unsigned int k;           //k Hash function
    unsigned int m;           //m bite list
    unsigned int n;           //inpu n data
    bool *M;






public:
    bloom();
    bloom(unsigned int n,unsigned int m, unsigned int k);
    void insert(unsigned int a,unsigned int b);
    bool check(unsigned int a,unsigned int b);
    void insert(unsigned int a,unsigned int b,unsigned int c,unsigned int d);
    bool check(unsigned int a,unsigned int b,unsigned int c,unsigned int d);
    ~bloom();

};

#endif
