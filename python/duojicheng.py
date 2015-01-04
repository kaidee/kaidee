#!/usr/bin/env python
# coding: utf-8

'''

'''

list = [4,8,3,5,2,1,6,7,0,9,2]
li = [1,2,3,4]

class ParrentClass(object):
	"""docstring for ParrentClass"""
	def __init__(self):
		print 'ParrentClass __init__ has called'
		self.name = 'ParrentClass'

class ParrentClass2(object):
	"""docstring for ParrentClass2"""
	def __init__(self):
		print 'ParrentClass2 __init__ has called'
		self.name1 = 'ParrentClass2'

class ChildClass(ParrentClass, ParrentClass2):
	"""docstring for ChildClass"""
	def __init__(self):
		super(ChildClass, self).__init__()
		# ParrentClass.__init__(self, _height)
		# self._height = _height
		# self.name = 'Baby'
		
	

def main():
	child = ChildClass()
	print child.name1
	

if __name__ == '__main__':
    main()