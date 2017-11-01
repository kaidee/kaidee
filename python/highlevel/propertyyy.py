#!/usr/bin/env python
# coding: utf-8
# Author:kaidee

# 属性


class Person(object):
    """docstring for Person"""
    def __init__(self, name):
        super(Person, self).__init__()
        self._name = name

    @property
    def name(self):
        "name property docs"
        print 'fetch...'
        return self._name

    @name.setter
    def name(self, value):
        print 'change...'
        self._name = value

    @name.deleter
    def name(self):
        print 'remove...'
        del self._name


def main():
    lee = Person('kaidee')
    print lee.name
    lee.name = 'Mathison'
    print Person.name.__doc__
    del lee.name


if __name__ == '__main__':
    main()
