#include<iostream>
using namespace std;
#include<math.h>
#include<iomanip>
class Animal
{
public:
	int age;
public:
	Animal(){cout<<"基类构造函数。"<<endl;}
	~Animal(){cout<<"基类析构函数。"<<endl;}

};
class Dog : private Animal
{
public:
	Dog(){cout<<"派生类构造函数。"<<endl;}
	//~Dog(){cout<<"派生类析构函数。"<<endl;}
	void SetAge(int n){ age=n;}
};
int main()
{
	Dog a;
	a.SetAge(10);
	return 0;
}