#!/usr/bin/python
# coding: utf-8

# 归并排序

def mergeSort(L,start,end):
    assert(type(L)==type(['']))
    length = len(L)
    if length==0 or length==1:
        return L
    def merge(L,s,m,e):
        left = L[s:m+1]
        right = L[m+1:e+1]
        while s<e:
            while(len(left)>0 and len(right)>0):
                if left[0]>right[0]:
                    L[s] = left.pop(0)
                else:
                    L[s] = right.pop(0)
                s+=1
            while(len(left)>0):
                L[s] = left.pop(0)
                s+=1
            while(len(right)>0):
                L[s] = right.pop(0)
                s+=1
            pass

    if start<end:
        mid = int((start+end)/2)
        mergeSort(L,start,mid)
        mergeSort(L,mid+1,end)
        merge(L,start,mid,end)

    return L

list = [8,3,5,2,1,6,7,0]

def main():
    print mergeSort(list, 0, len(list))

if __name__ == '__main__':
    main()