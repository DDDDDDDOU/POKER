#ifndef RBT_H
#define RBT_H



class RBT
{
private:
    enum color{Black,Red};
    int Rnum;
    int Bnum;
    int Nnum;
    int rrnum;
    int bheight;
    struct node{
        int key;
        int height;
        node *left;
        node *right;
        color co;
        node(int k,color c);
    };
    node *root;

public:
    RBT();
    ~RBT();
    void setcolor(node *t,color c);
    node* father(node *t);
    void  LLrotate(node *t);
    void  LRrotate(node *t);
    void  RRrotate(node *t);
    void  RLrotate(node *t);
    void rebanlance(node*t);
    void  insert(int k);
    void insert(int *p);
    bool exist(int k);
    bool isblack(node* t);
    int getB();
    int getR();
    int getN();
    int getH();
    int getRRN();
    int getBH();
    int height(node* t);
};

#endif // RBT_H
