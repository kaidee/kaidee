#!/usr/bin/env python
# coding: utf-8
# author: kaidee

def fib(num):
	n, a, b = 0, 0, 1
	while n < num:
		yield b
		a, b = b, a + b
		n += 1

if __name__ == '__main__':
	MAX = 5000
	f = fib(MAX)
	s = reduce(lambda x, y: x + y, [next(f) for _ in xrange(MAX)])
	print s

