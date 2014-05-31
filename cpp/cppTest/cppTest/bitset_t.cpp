//
//  bitset_t.cpp
//  cppTest
//
//  Created by Kaidee Lee on 5/31/14.
//  Copyright (c) 2014 Kaidee Lee. All rights reserved.
//

#include "bitset_t.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <bitset>

using namespace std;

void bit_set()
{
	bitset<32> bitvec(0xffffff);
//    bitvec.reset();
    bitvec.flip();
	for (int i = 0; i != 32; ++i)
	{
		/* code */
		cout<<bitvec[i];
	}
    cout<<endl;
    cout<<bitvec.none();
}