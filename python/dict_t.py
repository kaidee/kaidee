#!/usr/bin/env python
# coding: utf-8

# import os
import os,fnmatch
import allImagesList as IL
# import subprocess


# all_images = {'name':'Han', 'myname':'Kaidee',}

def getv(name):
	return IL.all_images.get(name)

# print(getv("name"))
# print(getv("myname"))
print(getv("bg0010000"))
