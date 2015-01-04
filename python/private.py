#!/usr/bin/env python
# coding: utf-8

'''
最少以两个下划线”__”开头；
最多以一个下划线”_”结尾，
在类的定义中，一旦遇到形如__attribute的成员，
python解释器会将它替换为_classname__attribute的形式，
所以形式上无法从外围访问到，但是找到改变后的私有属性，同样可以操作。
'''

list = [4,8,3,5,2,1,6,7,0,9,2]
li = [1,2,3,4]

class Test():
	"""docstring for Test"""
	def __init__(self):
		self.__price = 'price'

		

def main():
	a = Test()
	print vars(Test)
	print vars(a) #_Test__price


if __name__ == '__main__':
    main()