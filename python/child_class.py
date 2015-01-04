#!/usr/bin/env python
# coding: utf-8

'''
如果父类定了了__init__，子类需要显式的调用
'''

list = [4,8,3,5,2,1,6,7,0,9,2]
li = [1,2,3,4]

class ParrentClass(object):
	"""docstring for ParrentClass"""
	def __init__(self, _height):
		self.height = _height
		self.name = 'Dad'

class ChildClass(ParrentClass):
	"""docstring for ChildClass"""
	def __init__(self, _height, _weight):
		super(ChildClass, self).__init__(_height)
		# ParrentClass.__init__(self, _height)
		# self._height = _height
		self.weight = _weight
		self.name = 'Baby'
		
	

def main():
	parrent = ParrentClass(170)
	child = ChildClass(169, 62)
	print parrent.height
	print child.height
	print child.weight
	

if __name__ == '__main__':
    main()