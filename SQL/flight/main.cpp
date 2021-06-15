

#include <cstdlib>
#include <iostream>
#include <string.h>
using namespace std;
#define nn 10000

int main(){
    //  srand(time(NULL));
    // int ID=10000;
    // string Name;
    // int Phone_Number=54749110;
    // string Nationality="中国";
    // int shenfen;
    // int AccountID=12345678;

    // for(int i=0;i<nn;i++){
    //     Name='a'+to_string(i);
    //     cout<<"insert into `User` values(\'"<<ID<<"\',\'"<<Name<<"\',\'"<<Phone_Number
    //     <<"\',\'"<<Nationality<<"\');"<<endl;
    //     cout<<"insert into `User_Role` values(\'"<<ID<<"\',\'"<<1<<"\');"<<endl;
        
    //     cout<<"insert into `User_Account` values(\'"<<ID<<"\',\'"<<AccountID<<"\');"<<endl;

    //     cout<<"insert into `Account` values(\'"<<AccountID<<"\',\'"<<rand()<<"\');"<<endl;
    //     ID++;
    //     Phone_Number++;
    //     AccountID+=2;


    // }
    
//     cout<<"start TRANSACTION;"<<endl;

//     cout<<"set FOREIGN_KEY_CHECKS=0;"<<endl;
// int flightID=2000;
//     for(int i=0;i<500;i++){
//         cout<<"insert into `Filght_State` values(\'"<<flightID<<"\',\'"<<6<<"\');"<<endl;
//         flightID++;
//     }
//  flightID=2000;
//     for(int j=0;j<300;j++){
//         for(int i=0;i<500;++i){
//           cout<<"insert into `Flight_Ticket` values (\'"<<flightID<<"\',\'"<<flightID*1000+j+1<<"\');"<<endl;
//           flightID++;
//         }
//         flightID=2000;
//     }
    

for(int i=0;i<100000;++i){
    cout<<"insert into `123` values (\'"<<rand()<<"\',"<<rand()<<"."<<rand()%100<<");"<<endl;
}


}