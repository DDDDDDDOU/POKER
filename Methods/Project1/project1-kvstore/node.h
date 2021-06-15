#pragma once
#include <cstdlib>
#include <string>
using namespace std;
 struct node
	{
		uint64_t key;
		string value;
		node *up;
		node *down;
		node *succ;
		node *pred;
		node();
		node(uint64_t key,const string &s);
		void Delete(node *t);
	};