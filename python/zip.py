#!/usr/bin/env python
# coding: utf-8

'''
Zip用于同时执行多个序列的循环，与enumerate不同，zip属于函数，有它自己的返回值。
'''

list = [4,8,3,5,2,1,6,7,0,9,2]
li = [1,2,3,4]

def main():
	print zip(list,li)
	print globals()

if __name__ == '__main__':
    main()