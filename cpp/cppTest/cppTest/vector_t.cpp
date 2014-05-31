//
//  vector_t.cpp
//  cppTest
//
//  Created by Kaidee Lee on 5/31/14.
//  Copyright (c) 2014 Kaidee Lee. All rights reserved.
//

#include "vector_t.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

int vec()
{
	vector<string> ivec4(4, "kaidee");
	for (std::vector<string>::const_iterator ix = ivec4.begin(); ix != ivec4.end(); ++ix)
	{
	    cout<<"ivec4:"<<*ix<<endl;
//        *ix = " ";
	}

    cout<<ivec4.size();
	return 1;
}
