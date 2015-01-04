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

	int d = static_cast<int>(Milkshakes.size());
	cout<<"size: "<<d<<endl;
	// printf("%d\n", d);

	int dd = int(Milkshakes.size());
	cout << dd <<endl;
	return 0;
}