#include "common.h"

using namespace std;
#define db double
using namespace std;
const db cmp=1e-8;



bool contains(int a,vector<int> x){
	for(int i=0;i<x.size();++i){
		if(x[i]==a) return true;
		
	}
	return false;
}

void Gauss(int n,db **a){

    for(int i=0;i<n;i++){
        int max=i;
        for(int j=i+1;j<n;j++)
            if(fabs(a[j][i])>fabs(a[max][i]))
                max=j;
        // if(fabs(a[max][i])<cmp){
        //     puts("No Solution");
        //     return ;
        // }                               /**** 无解情况，本题不需要考虑 ****/ 
		
        for(int j=i;j<=n;j++)
            swap(a[i][j],a[max][j]);

        for(int j=0;j<n;j++){
            if(j==i) continue;
            db rate=a[j][i]/a[i][i];
            for(int k=i;k<=n;k++)
                a[j][k]-=a[i][k]*rate;
        }
    }
//	cout<<"Gauss:"<<endl;
//此处高斯消元算法参考自网络
}




//You should only code here.Don't edit any other files in this 
int func1(int amount, vector<int>& coins)
{	
	//cout<<amount<<endl;
	if(coins.empty()) return 0;
	int dp[amount];

	for  (int i=0;i<amount;++i) {
		dp[i]=0;
	}//初始化
	for(int n=0;n<coins.size();++n){
		for(int m=0;m<amount;++m){
			if(coins[n]>m+1){
				//C[n]>m时
				dp[m]=dp[m];//不改变
			}
			else if(coins[n]==m+1){
				dp[m]+=1;//C[n]=m时，多一种组合
			}
			else {
				//C[n]<m时
				dp[m]=dp[m]+dp[m-coins[n]];
			}
		}
	}
	
	return dp[amount-1];

}

int func2(int amount, vector< vector<int> >& conquer)
{
	int n=conquer.size();
	
	int dp[n][n];
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j) {
			dp[i][j]=0;
		}
		
	}
	for(int i=0;i<n;++i) dp[i][(i+1)%n]=1;//相邻两者可以决斗
	int start ,end;//相当于选中的A和B
	for(int i=1;i<n;++i){//AB之间间隔人数，i=0的情况已经包含在初始化中
		for(start=0;start<n;++start){//A一次取每一人
			end=(start+i+1)%n;
			for(int j=(start+1)%n;j!=end;j=(j+1)%n){
				if(dp[start][j]==1&&dp[j][end]==1&&(conquer[start][j]==1||conquer[end][j]==1)){
					dp[start][end]=1;
				}
			}
		}
	}
	
	int count=0;
	for(int i=0;i<n;++i){
		if(dp[i][i]==1) count++;
	}
	return count;
	
}


double func3(int n,int hp,vector<int>& damage,vector<int>& edges) {
	//if(n!=5) return -1;
	int m=edges.size()/2;//边数
	double dp[hp][n];//dp[i][j]表示剩余i+1点hp到达j+1点的期望次数
	vector<vector<int> > conj;//记录相邻点
	conj.resize(n);
	int fn=0;
	vector<int> var;//未知数列表
	vector<int> con;//常数项列表
	for(int i=0;i<n;i++) {
		if(damage[i]!=0) {
			
			con.push_back(i+1);
		}
		else {
			
				fn++;//方程数量,或者是未知数的数量，终点也算在内（起初终点没算做未知数）

				var.push_back(i+1);
			
		}
	}
	double **argument=new double*[fn];//增广矩阵
	for(int i=0;i<fn;++i)  argument[i]=new double [fn+1];
	for(int i=0;i<fn;++i){
		for(int j=0;j<=fn;++j) argument[i][j]=0;
	}

	double dg[n];//存点的度
	for(int i=0;i<n;++i) dg[i]=0;
	for(int i=0;i<2*m;i+=2){
		dg[edges[i]-1]++;
		dg[edges[i+1]-1]++;
		conj[edges[i]-1].push_back(edges[i+1]);
		conj[edges[i+1]-1].push_back(edges[i]);
	}//生成相邻点表和度表
	
	
	for(int i =hp;i>0;--i){//对每一个hp循环
		//先计算damage不为0的路口
		for(int j=0;j<con.size();++j){
			if(i+damage[con[j]-1]>hp) dp[i-1][con[j]-1]=0;
			else {
				dp[i-1][con[j]-1]=0;
				for(int m=0;m<conj[con[j]-1].size();++m){
					
					if(conj[con[j]-1][m]==n) continue;
					dp[i-1][con[j]-1]+=dp[i+damage[con[j]-1]-1][conj[con[j]-1][m]-1]/dg[conj[con[j]-1][m]-1];
				}
			}
		}


		//然后计算damage为0的路口
		for(int j=0;j<var.size();++j){
			for(int m=0;m<var.size();++m){
				//先考虑其他未知数
				if(m==j) {
					argument[j][j]=1;
					continue;
				}
				 
				if(contains(var[m],conj[var[j]-1])){
					//如果该未知数与j相邻
					if(var[m]!=n) argument[j][m]=-(1/(double)dg[var[m]-1]);
				}
			}
			argument[j][fn]=0;
			for(int m=0;m<con.size();++m){
				//考虑常数项
				if(contains(con[m],conj[var[j]-1])){
					//该常数项与未知数j相邻
					argument[j][fn]+=dp[i-1][con[m]-1]/dg[con[m]-1];
				}
				else continue;
			}
			

		}
		if(i==hp) argument[0][fn]+=1;
		
		 Gauss(fn,argument);//高斯消元
		 
		for(int j=0;j<var.size();++j){
			dp[i-1][var[j]-1]=argument[j][fn]/argument[j][j];
		}
		
	}// 生成增广矩阵

	double rate=0;
	

	for(int j=0;j<hp;j++){//计算期望次数
		rate+=dp[j][n-1];
	}
	// cout<<"argument:"<<endl;
	// 	for(int m=0;m<hp;++m){
	// 		for(int j=0;j<n;++j) cout<<dp[m][j]<<'\t';
	// 		cout<<endl;
	// 	}
	
	for(int i=0;i<fn;++i){
		delete [] argument[i];
	}
	delete [] argument;
    return rate;
}