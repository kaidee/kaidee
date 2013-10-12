#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	string line;
	while (getline(cin, line))
		cout << line << endl;
	return 0;
}