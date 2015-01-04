#!/usr/bin/env python
# coding: utf-8

'''
闭包
'''

def generate_power_func(n):
	print 'id(n): %X' % id(n)
	def nth_power(x):
		return x**n
	print 'id(nth_power): %X' % id(nth_power)
	return nth_power
		
	

def main():
	generate_power_func(1)
	

if __name__ == '__main__':
    main()