#!/usr/bin/env python
# coding: utf-8

import os

# input_dir = 'tga/output/中间版本角色/zs_东方刺客_001006/zs_东方刺客_001006'
input_dir = 'tga/test'

def main():
	os.chdir(input_dir)
	for dir_item in os.listdir('.'):
		if dir_item.endswith('.png'):
 			print 'dir_item: ', dir_item
 			print 'new: ', 'zs'+dir_item[2:]
 			print 'cat: ', dir_item[3:16]
			# os.rename(dir_item, 'zs'+dir_item[2:])

if __name__ == '__main__':
	main()