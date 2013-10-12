#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// template<typename T>
// class ddd {

// T t;
// T max(T const & a, T const & b)
// {
// 	return (a>b)?a:b;
// }
// };
int main(int argc, char const *argv[])
{
    vector<int> ivec(10);
    // ivec.push_back(2);
    vector<int> ivec2(ivec);
    vector<int> ivec4(10, 9);
    vector<string> ivec5(4, "kaidee");
    // vector<int> ivec;
    // vector<int> ivec;
    cout << "ivec:" <<ivec[0] <<endl;
    cout << "ivec:" <<ivec2[0] <<endl;
    cout << "ivec:" <<ivec4[0] <<endl;
    cout << "ivec:" <<ivec5[0] <<endl;

    for (std::vector<int>::iterator ix = ivec4.begin(); ix != ivec4.end(); ++ix)
    {
        cout<<"ivec4:"<<*ix;
    }
    cout<<endl;
    for (std::vector<int>::iterator iter = ivec4.begin(); iter != ivec4.end(); ++iter)
    {
        *iter = 0;
    }

    for (std::vector<int>::iterator i = ivec4.begin(); i != ivec4.end(); ++i)
    {
        cout<<" i: "<<*i;
    }
    cout<<endl;
    

    // init vector
    const list<int>::size_type list_size = 64;
    list<string> slist(list_size, "eh?");
    for (std::list<string>::iterator i = slist.begin(); i != slist.end(); ++i)
    {
        cout<<*i<<"  ";
    }
    // insert
    ivec5.insert(ivec5.begin(), " love ");
    ivec5.insert(ivec5.begin(), "ling");
    ivec5.insert(ivec5.end(), 4, " very much");
    ivec5.pop_back();

    for (std::vector<string>::const_iterator i = ivec5.begin(); i != ivec5.end(); ++i)
    {
        // cout<<endl;
        cout<<"  "<<*i;
    }
    cout<<endl;
    cout<<ivec5.at(0)<<endl;
    return 0;
}