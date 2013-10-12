#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main(int argc, char const *argv[])
{
    // string str("some string");
    // for (string::size_type ix = 0; ix != str.size() ; ++ix)
    // {
    //     /* code */
    //     cout << str[ix] << endl;
    // }

    // bool r = isalpha(str[2]);
    // cout << "r:" << r << endl;
    

    // for (string::size_type ix = 0; ix != str.size() ; ++ix)
    // {
    //     /* code */
    //     str[ix] = '*';
    // }
    // cout << str << endl;

    // string s = "max(3,5)";
    // string s2(s);
    // string s3("value");
    // string s4(5, 'C');
    // cout<<s<<endl;
    // cout<<s2<<endl;
    // cout<<s3<<endl;
    // cout<<s4<<endl;

    string s;
    // string::iterator iter = s.begin();
    // while (iter != s.end())
        // cout << *iter++ ;
    for (int i = 0; i < 10; ++i)
    {
        s.append("Hiya ");
    }
    cout<<s<<endl;
    cout<< s.find("ya");
    cout<< s.rfind("ya");
    cout<< s.find_first_of("a ");
    cout<<endl;

    return 0;
}