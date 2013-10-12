#include <iostream>
// #include <string>
// #include <map>

using namespace std;

class Base
{
public:
	virtual void print(){cout<<"Base";}

	/* data */
};

class Derived:public Base
{
public:
	void print(){cout<<"Derived";}

	/* data */
};

int main(int argc, char const *argv[])
{
	/* code */
	Base *point = new Derived();
	point->print();
	return 0;
}