#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	cout<<"host name:"<<endl;
	char strName[128];
	cout<<GetComputerName((char *)strName,128)<<endl;
	// cout<<gethostname((char *)strName,sizeof(strName))<<endl;
	// cout<<gethostbyname(strName)<<endl;

	return 0;
}
