#!/usr/bin/env python
# coding: utf-8

'''
静态方法和类方法
类方法不需要代表实例对象的参数self，
但它同样接受一个代表类对象参数，参数名字不固定，
习惯上使用cls，这个参数会将类对象的属性传入到方法中，
它是类对象的自身的引用，所以类方法中可以对类属性进行任何读写操作。
当然，python解释器不能够智能的去区分实例方法和类方法，
类中默认的方法都是实例方法。类方法是后加入python中的一种特征，
所以我们需要显式的告诉python解释器，这个方法是类方法。
'''

list = [4,8,3,5,2,1,6,7,0,9,2]
li = [1,2,3,4]

class Test():
	"""docstring for Test"""
	def __init__(self):
		pass
		# self.arg = arg
	class_data = "class data"
	def instance_func(self):
		self.instance_data = "instance data"
		print self.instance_data
	def static_func():
		static_data = 'static data'
		print static_data
	static_func = staticmethod(static_func)

	def class_func(cls):
		cls.class_data = 'class data 2'
		print cls.class_data
	class_func = classmethod(class_func)

class XTest():
	"""docstring for Test"""
	def __init__(self):
		pass
		# self.arg = arg
	class_data = "class data"
	def instance_func(self):
		self.instance_data = "instance data"
		print self.instance_data
	@staticmethod
	def static_func():
		static_data = 'static data'
		print static_data
	@classmethod
	def class_func(cls):
		cls.class_data = 'class data 2'
		print cls.class_data

def main():
	test = XTest()
	# Test.instance_func(test)
	test.instance_func()
	# Test.static_func()
	test.static_func()
	# Test.class_func()
	test.class_func()
	# print Test.class_data
	# print test.class_data

if __name__ == '__main__':
    main()