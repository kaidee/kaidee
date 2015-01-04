#!/usr/bin/env python
# coding: utf-8

class Messenger():
	"""docstring for Messenger"""
	def __init__(self, **kwargs):
		self.__dict__ = kwargs

m = Messenger(info="some information", b=['a'])
m.more = 22
# print m.info, m.b, m.more
print m.__doc__