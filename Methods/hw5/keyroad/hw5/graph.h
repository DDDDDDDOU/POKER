#pragma once
template <class TypeOfEdge>
class graph {
public:
	virtual bool insert(int u, int v, TypeOfEdge w) = 0; //²åÈë±ß
	virtual bool remove(int u, int v) = 0; //É¾³ı±ß
	virtual bool exist(int u, int v) const = 0; //±ßÊÇ·ñ´æÔÚ
	virtual int numOfVer() const { return Vers; }
	virtual int numOfEdge() const { return Edges; }
protected:
	int Vers, Edges;
};
