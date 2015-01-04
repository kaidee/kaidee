#!/usr/bin/env python
# coding: utf-8

'''
自省
'''

class ReflectSample(object):
	"""docstring for ReflectSample"""
	def runFunction(self, _funcName, *args, **kwds):
		self._funcName = _funcName
		if hasattr(self, _funcName):
			getattr(self, _funcName)(*args, **kwds)
		else:
			print 'No function ', _funcName
	def tenToTwo(*args, **kwds):
		print 'tenToTwo'
		
	

def main():
	foo = ReflectSample()
	print foo.runFunction('tenToTwo')
	print foo.runFunction('tenToEight')
	

if __name__ == '__main__':
    main()