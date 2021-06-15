#include "kvstore.h"
#include <string>
#include <iostream>
using namespace std;
KVStore::KVStore(const std::string &dir): KVStoreAPI(dir)
{
	srand(time(0));
	head = new node(0,"");
	tail = new node(UINT64_MAX,"");
	head->succ = tail;
	tail->pred = head;
	size = 0;
	 sst=new SStable;
	 //sst->Remove();

}

void KVStore::capacity(){
	cout<<"compact 次数；"<<sst->gettimes()<<endl;
	cout<<"compact 总时间："<<sst->gettime()<<endl;
}



KVStore::~KVStore()
{
	reset();
	delete head;
	delete tail;

}

/**
 * Insert/Update the key-value pair.
 * No return values for simplicity.
 */
void KVStore::put(uint64_t key, const std::string &s)
{
	Put(key, s, head, tail);
	return;
}

/*
 * Returns the (string) value of the given key.
 * An empty string indicates not found.
 */
std::string KVStore::get(uint64_t key)
{
	node *del=head->succ;
	while(del!=nullptr){
		if(del->key==key&&del!=tail) {
			return del->value;
			}

		if(del->key>key) break;
		del=del->succ;
	}//查找mmt
	return sst->get(key);//查找sst
}
/**
 * Delete the given key-value pair if it exists.
 * Returns false iff the key is not found.
 */
bool KVStore::del(uint64_t key)
{
	//memtable
	if(get(key)!="") {
		put(key,"");
		return true;
	}
	return false;
}

/**
 * This resets the kvstore. All key-value pairs should be removed,
 * including memtable and all sstables files.
 */
void KVStore::reset()
{
	//memtable
	clear();
	sst->Remove();
	//delete sst;
	//sst=new SStable;
//	sst->Remove();


	/*		 */	
	/*		 */
	/*sstable*/
	/*		 */
	/*		 */

	
	

}
void  KVStore::clear(){
	node *cur,*next;
	node *del;
	cur=head;
	while(cur->up!=nullptr) cur=cur->up;
	
	while (cur!=nullptr)
	{	next=cur;
		del=cur;
		while(next!=nullptr){
			del=next;
			next=next->succ;
			delete del;
		}
		cur=cur->down;

	}
	head = new node(0,"");
	tail = new node(UINT64_MAX,"");
	head->succ = tail;
	tail->pred = head;
	size=0;
}


void KVStore::display(){

	sst->showlist();
return;
}

node* KVStore::Put(uint64_t key, const std::string &s, node *h, node *t){
	node *tmp = h;
	node *ta  = t;
	while(tmp->succ->key < key) tmp = tmp->succ;
	if(tmp->succ->key == key&&tmp->succ != t) {//已经出现，换值
		node *ex = tmp->succ;
		size+=(sizeof(char)*s.size()-sizeof(char)*ex->value.size());
		while(ex){
			ex->value = s;
			ex=ex->up;
		}
		if(size>(1<<21)-128) {
			sst->putFile(head,tail);//转化成sst
			clear();
			}
		return nullptr;
	}//换值
	node *flg = tmp->succ;
	tmp->succ = new node(key,s);
	flg->pred = tmp->succ;
	tmp->succ->succ = flg;
	tmp->succ->pred = tmp;//插入该层
	node *ne = tmp->succ;

	if(h->up == nullptr){
			h->up = new node(0,"");
			t->up = new node(UINT64_MAX,"");
			h->up->down = h;
			t->up->down = t;
			t->up->pred = h->up;
			h->up->succ = t->up;
		}
	if(rand()%2==0){
		//如果可以生长
		tmp=h->up;
		ta =t->up;
		node *u = Put(key,s,tmp,ta);
		ne->up = u;
		u->down= ne;
	}
	if(h==head){
		size+=(sizeof(uint64_t)*2+sizeof(char)*s.size())+sizeof(int);
		if(size>(1<<21)-128) {
			sst->putFile(head,tail);//超过2m，转化成sst插入磁盘level0层
			clear();//清空mmt
			return nullptr;
			}
		

	}
	 
	return ne;
}