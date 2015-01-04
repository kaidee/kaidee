#!/usr/bin/env python
# coding: utf-8

def countSort(l):
    assert(type(l)==type(['']))
    length = len(l)
    if length==0 or length==1:
        return l
    m = max(l)
    ret = []
    storage = [0]*(m+1)
    def count(x):
        storage[x]+=1
    def pop(x):
        tem = storage[x]
        while tem>0:
            ret.append(x)
            tem-=1
    map(lambda x:count(x),l)
    # print l
    # map(lambda x:pop(x),xrange(m,0,-1))
    map(lambda x:pop(x),xrange(m,-1,-1))

    return ret




list = [4,8,3,5,2,1,6,7,0,9,2]

def main():
    print countSort(list)
    print sorted(list)

if __name__ == '__main__':
    main()