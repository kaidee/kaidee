#include <iostream>
#include <string>

using namespace std;

int test(int a);

int main(int argc, char const *argv[])
{
	// cout<<test<<endl;
	// cout<<main<<endl;
	// int(*fp)(int a);
	// fp = test;
	// cout<<fp(5)<<"|"<<(*fp)(10)<<endl;
	// x = cin.get();
	// cout<<x<<endl;

	string s("lingling");
	// string sp=&s;
	// cout<<sp<<endl;
	string* spp=&s;
	cout<<*spp<<endl;
	return 0;
}

int test(int a)
{
	return a;
}


