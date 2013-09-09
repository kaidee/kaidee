#include <iostream>
#include <string>

using namespace std;

template<typename T>

T max(T const & a, T const & b)
{
	return (a>b)?a:b;
}

int main(int argc, char const *argv[])
{
	int s = max(3,5);
	cout<<s<<endl;
	return 0;
}