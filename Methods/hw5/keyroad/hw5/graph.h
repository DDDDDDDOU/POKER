#pragma once
template <class TypeOfEdge>
class graph {
public:
	virtual bool insert(int u, int v, TypeOfEdge w) = 0; //�����
	virtual bool remove(int u, int v) = 0; //ɾ����
	virtual bool exist(int u, int v) const = 0; //���Ƿ����
	virtual int numOfVer() const { return Vers; }
	virtual int numOfEdge() const { return Edges; }
protected:
	int Vers, Edges;
};
