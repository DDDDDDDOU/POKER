#include "Dijkstra.h"
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

DijkstraProject2::DijkstraProject2(){
	pos=0;
	numG=0;
	G=nullptr;
	pre=nullptr;
}
/**
 * You should implement the methods:`readFromFile`,`run1`and`run2` here.
 */
bool DijkstraProject2::readFromFile(const char* inputfile)
{
	
	std::cout << "readFromFile: " << inputfile << std::endl;
	ifstream in(inputfile);

	if(!in.is_open()){
		cout<<"error"<<endl;
	}
	string buf;
	for(int i=0;i<pos;++i){
		getline(in,buf);
	}
	
	getline(in,buf);
	if(buf=="") return false;
	V=atoi(buf.substr(0,buf.find(",")).c_str());
	E=atoi(buf.substr(buf.find(",")+1).c_str());
	// if(G!=nullptr){
	// 	for(int i=0;i<V;++i) {
	// 		if(G[V]!=nullptr) delete[] G[V];
	// 		std::cout<<"V"<<endl;
	// 		}
	// 	delete []G;
	// }
	G=new int *[V];
	for(int i=0;i<V;++i) {
		G[i]=new int [V];
	}
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (i == j)G[i][j] = 0;
			else G[i][j] = 10000;
		}
	}
	
	int a,b,v;
	for(int i=0;i<E;++i){
		getline(in,buf);
		a=atoi(buf.substr(0,buf.find(",")).c_str());
		buf=buf.substr(buf.find(",")+1);
		b=atoi(buf.substr(0,buf.find(",")).c_str());
		v=atoi(buf.substr(buf.find(",")+1).c_str());
		G[a][b]=v;
	}
	
	pos+=E+2;
	numG++;
	in.close();
	return true;

	//TODO
}


void DijkstraProject2::run1(const char* outputFile)
{
	bool* mark = new bool[V];
	int* dist = new int[V];
	int tmp,minDist=10000;
	Npath = 0;
	pre = new vector<int>[V];
	for(int i=0;i<V;++i){
		mark[i]=false;
		pre[i].push_back(0);
		dist[i] = G[0][i];
	}
	mark[0] = true;
	for (int j = 0; j < V - 1; j++) {
		for (int i = 1; i < V; i++) {
			if (mark[i] == false && dist[i] < minDist) {
				minDist = dist[i];
				tmp = i;
			}
		}
		mark[tmp] = 1;
		for (int i = 1; i < V; i++) {
			if (i == tmp)continue;
			if (G[tmp][i] < 10000) {
				if (dist[i] > dist[tmp] + G[tmp][i]) {
					dist[i] = dist[tmp] + G[tmp][i];
					pre[i].clear();
					pre[i].push_back(tmp);
				}
				else if(dist[i] == dist[tmp] + G[tmp][i])pre[i].push_back(tmp);
			}
		}
		minDist = 10000;
	}
	dij(0, V - 1);
	ofstream out;
	if(numG!=1) out.open(outputFile,ios::app);
	else out.open(outputFile);
	out << dist[V - 1] << endl << Npath << endl;
	for (int i = 0; i < Npath; i++) {
		for (int j = 0; j < pathes[i].size(); j++) {
			if(j==0) out << pathes[i][j];
			else{out<<","<<pathes[i][j];}
		}
		out << endl;
	}
	out << endl;
	out.close();
	currentPath.clear();pathes.clear();
	Npath = 0;
	pre=nullptr;
	std::cout << "Save result to file:" << outputFile << std::endl;
}

void DijkstraProject2::dij(int s,int t) {
	
	if (s == t) 
	{
		currentPath.push_back(t);
		vector<int>tmp;
		for (int i = currentPath.size() - 1; i >= 0; i--) {
			tmp.push_back(currentPath[i]);
		}
		pathes.push_back(tmp);
		currentPath.pop_back(); 
		Npath++;
		return;
	}

	currentPath.push_back(t);

	for (int i = 0; i < pre[t].size(); ++i) {
		dij(s, pre[t][i]);
	}

	currentPath.pop_back();  
}


void DijkstraProject2::run2(const char* outputFile)
{
	int* preL;
	int * length;
	int * preV;
	int tmp;
	int min_len = 10000;
	preV = new int[V];
	preL = new int[V];
	length = new int[V];
	preL[0] = 0;
	for(int i=0;i<V;++i){
		preV[i]=0;
		length[0]=0;
	}
	stack<int> stac;
	stac.push(0);

	while (!stac.empty()) {
		
		tmp = stac.top();
		stac.pop();
		if (tmp == V - 1) {
			
			if (length[V - 1] == min_len) {
				int k = V-1;
				while (k != 0) {
					currentPath.insert(currentPath.begin(), k);
					k = preV[k];
				}
				currentPath.insert(currentPath.begin(), 0);
				pathes.push_back(currentPath);
				currentPath.clear();
				continue;
			}
			else if (length[V - 1] < min_len) {
				min_len = length[V - 1];
				pathes.clear();
				int k = V - 1;
				while (k != 0) {
					currentPath.insert(currentPath.begin(), k);
					k = preV[k];
				}
				currentPath.insert(currentPath.begin(), 0);
				pathes.push_back(currentPath);
				currentPath.clear();
				continue;
			}
			
		}
		for (int i = 1; i < V; i++) {
			if (G[tmp][i] != 10000 && G[tmp][i] > preL[tmp]) {
				preL[i] = G[tmp][i];
				preV[i] = tmp;
				length[i] = length[tmp] + G[tmp][i];
				stac.push(i);
			}
			
		}
	}
	
	ofstream out("output.txt", ios::app);
	out << min_len << endl << pathes.size() << endl;
	for (int i = 0; i < pathes.size(); i++) {
		for (int j = 0; j < pathes[i].size() - 1; j++) {
			out << pathes[i][j] << ",";
		}
		out << pathes[i][pathes[i].size() - 1] << endl;
	}
	out << "end"<<endl<<endl;
	out.close();
	std::cout << "Save result to file:" << outputFile << std::endl;

	//TODO
}
