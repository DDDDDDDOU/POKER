// #ifndef KVSTORE
// #define KVSTORE
#pragma once
#include <cstdlib>
#include <string>
using namespace std;
#include "kvstore_api.h"
#include "SStable.h"
#include "node.h"


class KVStore : public KVStoreAPI {
	// You can add your implementation here
private:
	SStable *sst;
	
	int size;
	node *head;
	node *tail;
public:
friend class SStable;
	KVStore(const std::string &dir);
	~KVStore();
	void put(uint64_t key, const std::string &s) override;//插入键值对
	node* Put(uint64_t key, const std::string &s, node *h,node *t);//重载put，在h-t层插入键值对
	void display();
	void clear();//清空mmt
	void grow(node *t);//层数生长
	std::string get(uint64_t key) override;
	bool del(uint64_t key) override;//删除键值对
	void reset() override;//清空mmt和所有sst
	void capacity();
};
//#endif