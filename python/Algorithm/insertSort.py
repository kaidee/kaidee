#!/usr/bin/env python
# coding: utf-8

def insertSort(L):
    assert(type(L)==type(['']))
    length = len(L)
    if length==0 or length==1:
        return L
    for i in xrange(1,length):
        value = L[i]
        j = i-1
        while j>=0 and L[j]<value:
            L[j+1] = L[j]
            j-=1
        L[j+1] = value
        print L
    print '============='
    return L


list = [4,8,3,5,2,1,6,7,0,9]

def main():
    print insertSort(list)

if __name__ == '__main__':
    main()