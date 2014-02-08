#include <iostream>
#include <string>
#include <vector>

using namespace std;


#pragma mark 获取UTF-8字符串长度
int strLength(const std::string &str)
{   
    if (typeid(str) == typeid(std::string) && str.length() > 0)
    {
        int len = str.length();
        std::vector <std::string> dump;
        int i = 0;
        while(i < len)
        {
            if (~(str.at(i) >> 8) == 0) {
                dump.push_back(str.substr(i, 3));
                i += 3;
            } else {
                dump.push_back(str.substr(i, 1));
                i += 1;
            }
        }
        return dump.size();
    } else {
        printf("str is not string\n");
        return 0;
    }
}

int main(int argc, char const *argv[])
{
    string s("中国人a1,");
    cout<<"length: "<<strLength(s)<<endl;
    cout<<"strlen: "<<strlen(s.c_str())<<endl;
    cout<<"sizeof: "<<sizeof(s.c_str())<<endl;
    return 0;
}