#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

int main(int argc, char const *argv[])
{
	list<string> Milkshakes;
	Milkshakes.push_back("Chocolate"); //实例化
	Milkshakes.push_back("Strawberry");
	Milkshakes.push_front("Lime");
	Milkshakes.push_front("Vanilla");

	cout<<"size: "<<typeid(Milkshakes.size()).name()<<endl;
	return 0;
}