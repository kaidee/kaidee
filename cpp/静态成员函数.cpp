#include<iostream>
using namespace std;
#include<math.h>
#include<iomanip>
class Application
{public:
	static void f();
	static void g();
private:
	static int global;
	
};
int Application::global=0;
void Application::f()
{
	global=5;
}
void Application::g()
{	cout<<global<<endl;	}
int main(void)
{
Application::f();
Application::g();
return 0;
}