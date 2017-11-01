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


class Student(object):
    def __init__(self):
        self._birth = 0

    @property
    def birth(self):
        return self._birth

    @birth.setter
    def birth(self, value):
        if value > 2015:
            raise ValueError, 'you are too yong!!!'
        self._birth = value

    @property
    def age(self):
        return 2014 - self._birth


def main():
    c = Circle(4)
    print c.area
    c.area = 100
    print c.area

    student = Student()
    student.birth = 2019
    print student.birth
    print student.age
    # student.age = 15

if __name__ == '__main__':
    main()