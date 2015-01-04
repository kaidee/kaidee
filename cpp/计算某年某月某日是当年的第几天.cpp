//

#include<iostream>
using namespace std;

/*
给出年、月、日，计算该日是该年的第几天。
*/

bool IsLeadYear(int y)
{
	if((y%4==0&&y%100!=0)||(y%400==0)) return true;//是闰年
	else return false;//不是闰年 
}

int main()
{	
	int year, month, date, sum=0;
	int a[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	cout<<"input year, month, date:";
	cin>>year>>month>>date;
	if (IsLeadYear(year))
	{
		a[1] = 29;
	}
	for (int i = 0; i < month-1; ++i)
	{
		sum += a[i];
	}
	sum += date;
	cout<<"你输入的日期是当年的第"<<sum<<"天";
	// cout<<"你输入的日期是当年的第"<<sum<<"天";

	cout<<endl;
}