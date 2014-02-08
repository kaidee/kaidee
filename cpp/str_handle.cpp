#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main(int argc, char const *argv[])
{
	char st[100];
	char st1[100] = {'h','e','l','l',};
	char st2[100] = {'h','e','l','l','o'};
	cout<<st<<endl;
	cout<<st1<<endl;
	cout<<st2<<endl;
	cout<<strlen(st1)<<endl;
	cout<<strcmp(st1,st2)<<endl;
	cout<<strncmp(st1,st2, 2)<<endl;
	cout<<strcat(st1,st2)<<endl;
	cout<<strncat(st1,st2, 2)<<endl;
	cout<<strcpy(st1,st2)<<endl;


	string str("HanHanHan");
	string str2("HanHan");
	cout<<endl;
	cout<<str.length()<<endl;
	cout<<str.size()<<endl;
	cout<<str.compare(str2)<<endl;

	return 0;
}