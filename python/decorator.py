#!/usr/bin/env python
# coding: utf-8

'''

'''

list = [4,8,3,5,2,1,6,7,0,9,2]
li = [1,2,3,4]

class Account():
	"""docstring for Account"""
	def __init__(self, price):
		self.price = price

	@property
	def pricee(self): #居然是不能与成员变量同名
		print 'has called'
		if self.price>0:
			return self.price
		else:
			return 0
		# return 4
		

def main():
	account1 = Account(9.0)
	account2 = Account(-9.0)

	print account1.price
	print account2.pricee
if __name__ == '__main__':
    main()