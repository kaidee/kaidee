#include<iostream>
using namespace std;
#include<stdlib.h>
int main(int)
{
	int n ,k;
	int comm(int n,int k);
	cin>>n>>k;
	cout<<comm(n,k)<<endl;
	return 0;
}
int comm(int n,int k)
{
	if(k>n)
		return 0;
	else if(n==0||k==0)
		return 1;
	else
		return comm(n-1,k)+comm(n-1,k-1);
}