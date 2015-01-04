#!/usr/bin/env python
# coding: utf-8

'''
发生器其实就是yield关键字。
它的作用就是阶段性的在函数中返回数据，记住当前位置，
然后由next函数继续推动它执行后面的语句

Yeild返回的值由next或者send得到，yield的值由send赋给，
注意第一次迭代不能使用send(value)的形式，
必须使用next()或者send(None)的形式，因为第一次执行的时候，
并没有指定到yield的位置，也就是没有yiled来接收send所赋的值。

关键字yield记录了代码执行的位置，通过next或者send推进代码的执行，
整轮执行过程，本质是在完成一个方法的执行——这也就是iter的本质，
我们之前的for循环中也是类似的机制。
'''

def test():
	print '111'
	a = yield 1
	print a
	print '222'
	b = yield 2
	print b
	print '333'
	c = yield 3
	print c


		
	

def main():
	foo = test()
	a = foo.next()
	print a
	b = foo.next()
	print b
	c = foo.send('test')
	print c

if __name__ == '__main__':
    main()