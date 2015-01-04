#!/usr/bin/env python
# coding: utf-8

'''
enumerate()循环返回给定列表和其对应的索引值
注意enumerate只能用于循环枚举，不能直接作为函数使用。
'''

list = [4,8,3,5,2,1,6,7,0,9,2]
li = [1,2,3,4]

def main():
	for i in enumerate(list):
		print i

if __name__ == '__main__':
    main()