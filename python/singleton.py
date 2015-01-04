#!/usr/bin/env python
# coding: utf-8

'''
利用__new__实现单例模式
'''

list = [4,8,3,5,2,1,6,7,0,9,2]
li = [1,2,3,4]

class Singleton(object):
	"""docstring for Singleton"""
	_instance = None
	def __new__(cls, *arg, **kwds):
		if cls._instance == None:
			cls._instance = object.__new__(cls)
			cls._instance.name = 0
			print 'something'
		return cls._instance
		
		
	

def main():
	obj1 = Singleton()
	obj2 = Singleton()
	print obj1.name
	print obj2.name
	

if __name__ == '__main__':
    main()