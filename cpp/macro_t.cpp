#include <iostream>
#include <string>

using namespace std;

#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

int main(int argc, char const *argv[])
{
	int k = MAX(0x0f, 0x0f);
	cout<<"K: "<<k<<endl;
	return 0;
}