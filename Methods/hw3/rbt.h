#ifndef RBT_H
#define RBT_H



class RBT
{
private:
    enum color{Black,Red};
    int Rnum;
    int Bnum;
    struct node{
        int key;
        node *left;
        node *right;
        color co;
        node(int k,color c);
    };
    node *root;

public:
    RBT();
    ~RBT();
    node* father(node *t);
//    void  LLrotate(node *t);
//    void  LRrotate(node *t);
//    void  RRrotate(node *t);
//    void  RLrotate(node *t);
//    void rebanlance(node*t);
    void  insert(int k);
    void insert(int *p);
};

#endif // RBT_H
