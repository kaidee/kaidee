#include "stdafx.h"

using namespace std;

class A
{
private:
	int count;
public:
	A():count(0)
	{ 
		cout << "Can you see me Now!" << endl;
	}
	~A()
	{ 
		cout << "I'm Go Away!" << endl; 
	}
	void Inc()
	{ 
		count++; 
	}
	int Count()
	{ 
		return count; 
	}
};

void TestStatic(  )
{
	static A a;
	a.Inc();
	cout << "count's value is : " << a.Count() << endl;
}

//void main()
//{
//	cout << "Program Start!" << endl;
//	TestStatic();
//	TestStatic();
//	TestStatic();
//	cout << "Program End!" << endl;
//}