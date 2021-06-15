#include "node.h"
node::node(uint64_t key , const string &s){
	this->key = key ;
	this->value = s ;
	this->up = nullptr;
	this->down = nullptr;
	this->succ = nullptr;
	this->pred = NULL;
}

node::node(){
	this->up = nullptr;
	this->down = nullptr;
	this->succ = nullptr;
	this->pred = NULL;
}

void node::Delete(node *t){
	node *del=t;
	while(t!=nullptr){
		t=t->succ;
		delete del;
		del=t->succ;
	}
}