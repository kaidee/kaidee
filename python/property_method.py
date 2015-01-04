#!/usr/bin/env python
# coding: utf-8

'''
'''

from math import pi, sqrt

list = [4,8,3,5,2,1,6,7,0,9,2]
li = [1,2,3,4]

class Circle(object):
	"""docstring for Circle"""
	def __init__(self, radius):
		self.radius = radius
		
	def getArea(self):
		return self.radius * self.radius * pi
	def setArea(self, value):
		self.radius = sqrt(value/pi)	
	area = property(getArea, setArea, doc = None)
		
	

def main():
	c = Circle(4)
	print c.area
	c.area = 100
	print c.area
	

if __name__ == '__main__':
    main()