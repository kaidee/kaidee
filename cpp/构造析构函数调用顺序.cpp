#include<iostream>
using namespace std;
#include<math.h>
#include<iomanip>
class Animal
{
public:
	int age;
public:
	Animal(){cout<<"���๹�캯����"<<endl;}
	~Animal(){cout<<"��������������"<<endl;}

};
class Dog : private Animal
{
public:
	Dog(){cout<<"�����๹�캯����"<<endl;}
	//~Dog(){cout<<"����������������"<<endl;}
	void SetAge(int n){ age=n;}
};
int main()
{
	Dog a;
	a.SetAge(10);
	return 0;
}