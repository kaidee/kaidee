//

#include<iostream>

#include <string>
#include <vector>
#include <list>

using namespace std;

/*

写一函数用“气泡法”对输入的10个字符按由小到大的顺序排列。

*/

int main()
{	
	list<string> Milkshakes;
	Milkshakes.push_back("Chocolate"); //实例化
	Milkshakes.push_back("Strawberry");
	Milkshakes.push_front("Lime");
	Milkshakes.push_front("Vanilla");

	cout<<"size: "<<typeid(Milkshakes.size()).name()<<endl;

	cout<<endl;
}