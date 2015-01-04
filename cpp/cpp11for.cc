//for range

#include<iostream>
#include<map>
#include<string>
#include<vector>
using namespace std;

/*



*/

int main()
{	
	std::string str = "hello, world";
	for(auto ch : str) {
	     std::cout << ch << " ";
	}

	int arr[] = {1, 2, 3, 4};
	for(auto i : arr) {
	     std::cout<< i << std::endl;
	}

	std::vector<int> vb = {1, 2, 3};

	vector<string> str_vec = {"i", "like",  "google"};
	for(auto& it : str_vec) {
	     it = "c++";
	}

	map<int, string> hash_map = {{1, "c++"}, {2, "java"}, {3, "python"}};
	for(auto it : hash_map) {
	     std::cout << it.first << '\t' << it.second << std::endl;
	}



	cout<<endl;
}