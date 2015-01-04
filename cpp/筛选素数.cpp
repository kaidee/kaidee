//

#include<iostream>
#include<math.h>
using namespace std;

/*

用筛选法求100之内的素数。（所谓素数就是除了1和它本身以外，
不能再被别的整数整除，这种数称作素数(也称质数)。）

*/

int main()
{	
	int j, count = 100;
	for (int i = 1; i < count; ++i)
	{
		for (j = 2; j <= sqrt(i); ++j)
		{
			if (i % j == 0)
			{
				break;
			}
			// else break;
		}
		if (j > sqrt(i))
		{
			cout<<" "<<i;
		}
	}

	cout<<endl;
}