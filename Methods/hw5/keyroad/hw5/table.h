#pragma once
#include"graph.h"
#include<queue>
#include <iostream>
using namespace std;
template <class TypeOfVer, class TypeOfEdge>
class adjListGraph {
public:
	int numOfVer() const { return Vers; }
	int numOfEdge() const { return Edges; }
	int Vers, Edges;
public:
	adjListGraph(int vSize, const TypeOfVer d[]);
	bool insert(int u, int v, TypeOfEdge w);
	bool remove(int u, int v);
	bool exist(int u, int v) const;
	void topSort() const;//��������
	void criticalPath() const;//�ؼ�·��
	~adjListGraph();
public:
	struct edgeNode { //�ڽӱ��д洢�ߵĽ���� 
		int end; //���սڵ��� 
		TypeOfEdge weight; //�ߵ�Ȩֵ 
		edgeNode *next;
		edgeNode(int e, TypeOfEdge w, edgeNode *n = NULL)
		{
			end = e; weight = w; next = n;
		} //e��ʾ�ߵ��սڵ�
	};
	struct verNode { //���涥�������Ԫ������ 
		TypeOfVer ver; //����ֵ 
		edgeNode *head; //��Ӧ��������ͷָ��(edgeNode����)
		verNode(edgeNode *h = NULL) { head = h; }
	};
	verNode *verList; //ָ�򶥵�������ָ��
};

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[])
{ //����ֻ�нڵ��ͼ���߱���Ϊ��
	Vers = vSize;
	Edges = 0; //0����
	verList = new verNode[vSize]; //����߱��ռ�
	for (int i = 0; i < Vers; ++i) verList[i].ver = d[i]; //���ڵ�� 
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph()
{
	int i;
	edgeNode *p;
	for (i = 0; i < Vers; ++i)
		while ((p = verList[i].head) != NULL) {
			verList[i].head = p->next;
			delete p;
		}
	delete[] verList;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::insert(int u, int v, TypeOfEdge w)
{ //û���жϱ��Ƿ���ڣ��������ر�
	verList[u].head = new edgeNode(v, w, verList[u].head);
	//ע��������һ�У�
	//1. ����һ���µı߽ڵ㣬������= verList[u].head
	//2. verList[u].headָ���µı�
	//���������Ա�֤����Ϊ����ʱ��
	++Edges;
	/*cout << u << ":" << endl;
	edgeNode *p = verList[u].head;
	for (p = verList[u].head; p != NULL; p = p->next)
		cout << p->end;
	cout << endl;*/
	return true;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::remove(int u, int v)
{
	edgeNode *p = verList[u].head, *q;
	if (p == NULL) return false; //���uû�������ıߣ����� 
	if (p->end == v) {//�������еĵ�һ�������Ǳ�ɾ���ı� 
		verList[u].head = p->next; //��׼������ɾ������
		delete p; --Edges;
		return true;
	}
	while (p->next != NULL && p->next->end != v) p = p->next;
	if (p->next == NULL) return false; //û���ҵ���ɾ���ı� 
	q = p->next; p->next = q->next; delete q; --Edges; //�ҵ���ɾ��
	return true;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(int u, int v) const
{
	edgeNode *p = verList[u].head; //pָ��u�ı߱�
	while (p != NULL && p->end != v)
		p = p->next; //��u�ı߱�������û�е�v�ı�
	if (p == NULL)
		return false;
	else
		return true;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::topSort() const
{
	queue<int> q;
	edgeNode *p;
	int current, *inDegree = new int[Vers]; //���ڼ�¼�ڵ����
	for (int i = 0; i < Vers; ++i) inDegree[i] = 0;
	for (i = 0; i < Vers; ++i) {//����ÿ���ڵ��Ӧ�ı߱�
		for (p = verList[i].head; p != NULL; p = p->next)
			++inDegree[p->end]; //�߱��м�¼��ÿ���ڵ���ȼ�1
	}
	for (i = 0; i < Vers; ++i)
		if (inDegree[i] == 0) q.push(i); //�������Ϊ0�Ľڵ����
	cout << "��������Ϊ��" << endl;
	while (!q.empty()) {//������в�Ϊ����ѭ��
		current = q.pop(); //������ǰ���Ԫ��
		cout << verList[current].ver << '\t';
		for (p = verList[current].head; p != NULL; p = p->next)
			if (--inDegree[p->end] == 0) //���ӽڵ�ĺ����ȼ�1
				q.push(p->end); //���Ϊ0�Ľڵ����
	}
	cout << endl;
}


template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::criticalPath() const
{
	TypeOfEdge *ee = new TypeOfEdge[Vers], *le = new TypeOfEdge[Vers];
	int *top = new int[Vers], *inDegree = new int[Vers];
	//top������������Ľ��
	queue <int> q; //������������Ķ���
	int i;
	edgeNode *p;
	for (i = 0; i < Vers; i++) {//��ʼ�����
		inDegree[i] = 0;
	}
	for (i = 0; i < Vers; i++) {//�������
		
		for (p = verList[i].head; p != NULL; p = p->next)
		{
			++inDegree[p->end];
		}	
	} 
	//��ʼ��������
	for (i = 0; i < Vers; i++)
	{
		//��������Ϊ0�ĵ�
		if (inDegree[i] == 0) q.push(i);
	}
	i = 0;
	while (!q.empty()) {
		top[i] = q.front();
		
		q.pop();
		for (p = verList[top[i]].head; p != NULL; p = p->next)
		{
			inDegree[p->end]--;
			//�����̽ڵ����Ϊ0�������
			if (inDegree[p->end] == 0) q.push(p->end);
		}
		++i;
	}
	//�����������
	for (i = 0; i < Vers; i++) {
		cout << top[i] << ' ';
	}
	cout << endl;

	//����top = {1, 2, 3, 4, 5, 6}
	for (i = 0; i < Vers; i++) ee[i] = 0;
	
	for (i = 0; i < Vers; i++) {//�����ڵ�iʱ���޸�i�߱���
								//ֱ�Ӻ�̵�ee
		for (p = verList[top[i]].head; p != NULL; p = p->next)
			if (ee[p->end] < ee[top[i]] + p->weight)
				ee[p->end] = ee[top[i]] + p->weight;
	}
	cout << "ee" << endl;
	//���ee
	for (i = 0; i < Vers; i++)
	{
		cout << ee[top[i]]<<endl;
	}

	
	//for (i = 0; i < Vers; i++) le[i] = ee[Vers �C 1];
	for (i = 0;i < Vers;++i)le[i] = ee[top[Vers - 1]];
	for (i = Vers - 1; i >= 0; --i) {//�����ڵ�iʱ������i�߱��е�
									 //ֱ�Ӻ�̵�le�޸�le(i)
		for (p = verList[top[i]].head; p != NULL; p = p->next)
			if (le[p->end] - p->weight < le[top[i]])
				le[top[i]] = le[p->end] - p->weight;
	}
	cout << "le" << endl;
	//���le
	for (i = 0; i < Vers; i++)
	{
		cout << le[top[i]] << endl;
	}
	//�ҹؼ�·��
	for (i = 0; i < Vers; i++)
	{
		if (ee[top[i]] == le[top[i]])
			cout << "(" << verList[top[i]].ver << ")";
	}
		
}



