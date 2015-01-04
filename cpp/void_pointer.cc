//

#include<iostream>
using namespace std;

/*

*/

int main()
{	
	double obj = 3.14;
	double *pd = &obj;
	void *pv = &obj;
	// cout<< (pv == pd);
	// (double*)pv;
	// *pv = 2.2;

	cout<< sizeof(short);
	short short_value = 32767;
	short ival = 1;
	short_value += ival;
	cout << short_value;

	cout<<endl;
}