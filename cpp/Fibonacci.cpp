#include<iostream>
using namespace std;
#include<math.h>
#include<iomanip>
int main()
{
	long i;
	const double n=50;
	static double f[50]={1,1};
	for(i=2;i<n;i++)
		f[i]=f[i-2]+f[i-1];
	for(i=0;i<n;i++)
	{
		if(i%5==0)
			cout<<endl;
		cout<<setw(20)<<f[i];
	}
	cout<<endl;
	/*double c;
	c=34/55;
	cout<<c;
	cout<<endl;*/
	return 0;
}