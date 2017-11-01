#!/usr/bin/env python
# coding: utf-8
# author: kaidee

'''
闭包
'''

def generate_power_func(n):
    print 'id(n): %X' % id(n)
    def nth_power(x):
        return x**n
    print 'id(nth_power): %X' % id(nth_power)
    return nth_power

def count():
    fs = []
    for i in range(1, 4):
        def f(x):
            def g():
                return x*x
            return g
        fs.append(f(i))
    return fs

f1, f2, f3 = count()




def main():
    # generate_power_func(1)
    f1, f2, f3 = count()
    print f1(), f2(), f3()

if __name__ == '__main__':
    main()