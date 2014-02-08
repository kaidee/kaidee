#include <iostream>
#include <string>
// #include <vector>
// #include <list>

using namespace std;

class Base
{
private:
	int b_number;

public:
	Base(){};
	~Base(){};

	Base(int i):b_number(i){}
	int get_number(){return b_number;}
	void print(){cout << b_number <<endl;}
};

class Derived : public Base
{
private:
	int d_number;

public:
	Derived(int i, int j) : Base(i), d_number(j){};
	~Derived(){};

	void print()
	{
		cout << get_number() << " ";
		cout << d_number << endl;
	}
};

int main(int argc, char const *argv[])
{
	Base a(2);
	Derived b(3,4);
	cout << "a is ";
	a.print(); // 2
	cout << "b is ";
	b.print(); // 3 4
	cout << "base part of b is ";
	b.Base::print(); // 3

	return 0;
}



//Example:  non- virtual destructors for dynamically allocated objects.
 
// #include <iostream.h>
// #include <string.h>
// class Thing
// { public:
// virtual void what_Am_I( ) {cout << "I am a Thing./n";}
// ~Thing(){cout<<"Thing destructor"<<endl;}
// };
// class Animal : public Thing
// {  
// public:
// virtual void what_Am_I( ) {cout << "I am an Animal./n";}
// ~Animal(){cout<<"Animal destructor"<<endl;}
// };
// void main( )
// {
//    Thing *t =new Thing;      
//    Animal*x = new Animal;
//    Thing* array[2];
//    array[0] = t;                                // base pointer
//    array[1] = x;               
//     for (int i=0; i<2; i++)  array->what_Am_I( ) ;
//    delete array[0];
//    delete array[1];
//    return ;
// }

