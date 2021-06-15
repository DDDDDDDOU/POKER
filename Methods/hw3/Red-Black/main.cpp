#include <iostream>
#include "rbt.h"

using namespace std;

int main()
{
    RBT tree;
    int n;
    int key;
    cout<<"n:  "<<endl;
    cin>>n;
    for (int i=0;i<n;++i){
        cout<<"insert: ";
        cin>>key;
        tree.insert(key);
    }
    return 0;
}
