#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(int argc, char const *argv[])
{
	map<string, int> word_cont;
	map<string, int>::iterator map_it = word_cont.begin();
	cout << map_it->first;
	cout << " " << map_it->second <<endl;
	// map_it->first = "ling";
	// --map_it->second;
}
	// cout << map_it->first;
	// cout << " " << map_it->second <<endl;

	return 0;
}