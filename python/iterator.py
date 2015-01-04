#!/usr/bin/env python
# coding: utf-8

'''
类中的迭代机制，通过重载__iter__方法，返回一个带有next方法的对象来实现。
'''

class MyList(object):
	"""docstring for MyList"""
	def __init__(self):
		self.data = []
		self.index = 0
	def __iter__(self):
		return self
	def append(self, value):
		self.data.append(value)
	def next(self):
		while True:
			if self.index == len(self.data):
				raise StopIteration
			if self.data[self.index]%2 == 0:
				self.index += 1
			else:
				self.temp = self.data[self.index]
				break
		self.index += 1
		return self.temp
		
	

def main():
	my_list = MyList()
	for x in xrange(1,10):
		my_list.append(x)
	for i in my_list:
		print i
	

if __name__ == '__main__':
    main()