#include <iostream>
#include "kvstore.h"
#include <time.h>
using namespace std;

int main(){
	KVStore *store;
	clock_t start,end;
	start=end=0;
	float time=0;

	store=new KVStore("./data");
	store->reset();
	for(int m=0;m<8;++m){
		start=clock();
		for(int i=1024*m*8;i<1024*(m*8+8);++i){
			store->put(i,string(i+1,'x'));
		}
		end=clock();
		time+=float(end-start)/CLOCKS_PER_SEC;
		// cout<<"put次数:"<<1024*8*(m+1)<<"\t时间:"<<time<<endl;
		// cout<<"平均每秒put:"<<1024*8*(m+1)/time<<"次"<<endl;
		cout<<1024*8*(m+1)<<'\t'<<1024*8*(m+1)/time<<endl;

	}
	
	// time=0;
	// for(int m=0;m<10;++m){
	// 	start=clock();
	// 	for(int i=1024*m*8;i<1024*(m*8+8);++i){
	// 		store->get(i);
	// 	}
	// 	end=clock();
	// 	time+=float(end-start)/CLOCKS_PER_SEC;
	// 	cout<<"get次数:"<<1024*8*(m+1)<<"\t时间:"<<time<<endl;

	// }
	// time =0;
	// 	cout<<"平均每次get:"<<time*1000/(1024*8*10)<<"ms"<<endl;
	// for(int m=0;m<10;++m){
	// 	start=clock();
	// 	for(int i=1024*m*8;i<1024*(m*8+8);++i){
	// 		store->del(i);
	// 	}
	// 	end=clock();
	// 	time+=float(end-start)/CLOCKS_PER_SEC;
	// 	cout<<"delete次数:"<<1024*8*(m+1)<<"\t时间:"<<time<<endl;

	// }
	// 	cout<<"平均每次delete:"<<time*1000/(1024*8*10)<<"ms"<<endl;




    return 0 ;
}