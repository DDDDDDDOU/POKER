#include"table.h"
#include<iostream>

using namespace std;
int main()
{
	int ver[10] = { 0,1,2,3,4,5,6,7,8,9};
	int vsize = 10;
	adjListGraph<int,int> test(vsize,ver);
	test.insert(0, 3, 2);
	test.insert(0, 6, 38);
	test.insert(1, 2, 13);
	test.insert(1, 0, 12);
	test.insert(1, 4, 29);
	test.insert(1, 9, 9);
	test.insert(2, 4, 47);
	test.insert(2, 8, 28);
	test.insert(3, 4, 24);
	test.insert(3, 5, 14);
	test.insert(3, 6, 26);
	test.insert(4, 5, 16);
	test.insert(4, 6, 48);
	test.insert(4, 7, 14);
	test.insert(5, 7, 26);
	test.insert(5, 8, 1);
	test.insert(6, 7, 29);
	test.insert(6, 8, 11);
	test.insert(8, 7, 1);
	test.insert(9, 2, 42);
	test.insert(9, 0, 10);
	test.insert(9, 7, 31);
	
	test.criticalPath();
	system("pause");
	return 0;
}