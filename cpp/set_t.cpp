#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main(int argc, char const *argv[])
{
	vector<int> ivec;
	for (std::vector<int>::size_type i = 0; i !=10; ++i)
	{
		ivec.push_back(i);
		ivec.push_back(i);
	}
	set<int> iset(ivec.begin(), ivec.end());
	cout << ivec.size() << endl;
	cout << iset.size() << endl;


	return 0;
}