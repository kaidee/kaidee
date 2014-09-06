#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(int argc, char const *argv[])
{
	map<string, int> word_cont;
	typedef map<string, int>::value_type valType;
	word_cont.insert(map<string, int>::value_type("anna", 1));
	word_cont.insert(make_pair("annaa", 11));
	word_cont.insert(valType("annaaa", 111));

	cout << word_cont["anna"] <<endl;
	cout << word_cont["annaa"] <<endl;
	cout << word_cont["annaaa"] <<endl;

	cout << word_cont.count("anna") <<endl;
	// cout << word_cont.find("anna") <<endl;

	map<string, int>::iterator map_it = word_cont.find("anna");
	if (map_it != word_cont.end())
		cout << map_it->second <<endl;
	// cout << map_it->first;
	// cout << " " << map_it->second <<endl;
	// map_it->first = "ling";
	// --map_it->second;
// }
	// cout << map_it->first;
	// cout << " " << map_it->second <<endl;

	typedef pair<string, string> soulmate;
	soulmate one("Kaidee", "Han");
	cout<<one.first <<" miss " <<one.second <<endl;



	return 0;
}