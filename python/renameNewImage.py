#!/usr/bin/env python
# coding: utf-8

import os

# input_dir = 'tga/output/中间版本角色/zs_东方刺客_001006/zs_东方刺客_001006'
# input_dir = '../../android/client/resources/images/roleInfoWin/'
# input_dir = '../client/resources/images/task/'
# input_dir = '新切图/排行榜20140424/'
input_dir = '/Users/kaidee/Downloads/508'




def main():
	os.chdir(input_dir)
	for dir_item in os.listdir('.'):
		if dir_item.endswith('.png'):
 			# print 'dir_item: ', dir_item
 			# print 'new: ', 'n_'+dir_item
 			# print 'cat: ', dir_item[3:16]
			os.rename(dir_item, 'n_'+dir_item)
	print "Done......"

if __name__ == '__main__':
	main()