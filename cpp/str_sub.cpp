#include <iostream>
#include <string>
#include <vector>

using namespace std;

std::string sub(std::string str,int start,int end)
{
    
    if(typeid(str)==typeid(std::string) && str.length()>0)
    {
        int len=str.length();
        std::string tmp="";
        //先把str里的汉字和英文分开
        std::vector <std::string> dump;
        int i=0;
        while(i < len)
        {
            if (~(str.at(i) >> 8) == 0)
            {
                dump.push_back(str.substr(i,3));
                i=i+3;
                
            }
            else
            {
                dump.push_back(str.substr(i,1));
                i=i+1;
            }
        }
        end=end>0?end:dump.size(); 
        if(start<0||start>end)
            printf("start is wrong");
        for(i=start; i<=end; i++)
        {
            tmp+=dump[i-1];
        }
        return tmp;
    }
    else
    {
        printf("str is not string\n");
        return "";
        
    }
}

int main(int argc, char const *argv[])
{
	string s("ssdf汉字hjkl英文oiu");
	cout<<"subed string: "<<sub(s, 2, 8)<<endl;
	return 0;
}