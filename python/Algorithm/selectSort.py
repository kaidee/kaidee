#!/usr/bin/env python
# coding: utf-8

def selectSort(L):
    assert(type(L)==type(['']))
    length = len(L)
    if length==0 or length==1:
        return L

    def _max(s):
        largest = s
        for i in xrange(s,length):
            if L[i] > L[largest]:
                largest = i
        return largest
        
    for i in xrange(length):
        largest = _max(i)
        if i!=largest:
            temp = L[largest]
            L[largest] = L[i]
            L[i] = temp
    return L


list = [4,8,3,5,2,1,6,7,0,9]

def main():
    print selectSort(list)

if __name__ == '__main__':
    main()