#!/usr/bin/env python
# coding: utf-8

'''
语法：

[<expr1> for I in L if <expr2>]

推导式包括在一个for之后的表达式，零个或者多个for或if语句进行过滤，返回值是过滤后的元素组成的列表，其语意如下：

Result=[]
For k in L:
    if <expr2>:
    Result.append(<expr1>)
Return result
'''

list = [4,8,3,5,2,1,6,7,0,9,2]
li = [1,2,3,4]

def main():
	print [i*i for i in li if i>3]
if __name__ == '__main__':
    main()