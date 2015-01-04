#!/usr/bin/env python
# coding: utf-8

list = [4,8,3,5,2,1,6,7,0,9,2]
li = [1,2,3,4]

def main():
    # lii = filter(lambda x:x%2==0, li)
    lii = filter(lambda x:x%2==0, li)
    print lii
    print map(None, li, map(lambda x:x*x, li))
    print reduce(lambda x,y:x+y, li)

if __name__ == '__main__':
    main()