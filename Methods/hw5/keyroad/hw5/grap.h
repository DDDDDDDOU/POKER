#ifndef GRAP_H
#define GRAP_H

class graph{
private:
    int **table;//邻接表
    int **time;//开始时间表
    int n;
    int E;
    int *U;
    int numU;//子集大小
    int start,end;
public:
graph();
//graph(int start,int end);
void findway(int start,int end);
bool inU(int i);//判断节点i是否在U中
void ebway(int v);
void lbway(int v);
void output();


};

#endif // !GRAP_H
