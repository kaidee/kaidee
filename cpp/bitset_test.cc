//bitset

#include<iostream>
#include<bitset>

using namespace std;

/*


*/

int main()
{	
	string strval("1000");
	bitset<32> bitvec4(strval);
	cout<< bitvec4 <<endl; //00000000000000000000000000001110

	unsigned long a = 10;
	bitset<16> b(a);
	cout<< b <<endl;
	cout<< b.any() <<endl;
	cout<< b.none() <<endl;
	cout<< b.count() <<endl;
	cout<< b.size() <<endl;
	cout<< b[13] <<endl;
	cout<< b.flip() <<endl;
	cout<< b <<endl;

	cout<<endl;
}