#pragma once

#include <cstdint>
#include <string>
#include <fstream>
#include <climits>
#include <vector>
using namespace std;

/**
 * This file declare the main class of Project2:DijkstraProject2.
 * You should implement the methods:`readFromFile`,`run1`and`run2` in Dijkstra.cpp.
 * You can add anything in DijkstraProject2 class to implement Project2.
 */
class DijkstraProject2 {
private:
	//You can declare your graph structure here.
	int pos;
	int V;
	int E;
	int Npath;
	int numG;
	int** G;
	int read_pos;
	vector<int> currentPath;
	vector<vector<int> >pathes;
	vector<int>* pre;
	
	
	void dij(int s,int t);
public:

	DijkstraProject2();
	/**
	 * Read graph from Param:`inputfile`.
	 * 
	 */
	bool readFromFile(const char* inputfile="input.txt");
	
	/**
	 * Part 1, implement Dijkstra algorithm to finish Part 1
	 * and save the result to Param:`outputFile`.
	 * Save the path as: node_1,node_2...node_n. (seperate nodes with comma)
	 *
	 */
	void run1(const char* outputFile = "output.txt");

	/**
	 * Part 2, find the monotonically increasing path to finish Part 2
	 * and save the result to Param:`outputFile`.
	 * Save the path as: node_1,node_2...node_n. (seperate nodes with comma)
	 *
	 */
	void run2(const char* outputFile = "output.txt");

	//~DijkstraProject2();

};
