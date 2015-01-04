#!/usr/bin/env python
# coding: utf-8

def bubbleSort(L):
    assert(type(L)==type(['']))
    length = len(L)
    if length==0 or length==1:
        return L
    for i in xrange(length):
        for j in xrange(length-1-i):
            if L[j] < L[j+1]: 
                temp = L[j]
                L[j] = L[j+1]
                L[j+1] = temp
    return L




list = [4,8,3,5,2,1,6,7,0,9]

def main():
    print bubbleSort(list)

if __name__ == '__main__':
    main()