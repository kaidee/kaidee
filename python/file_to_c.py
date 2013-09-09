#!/usr/bin/env python
# coding: utf-8

"""
Usage:
  file_to_c.py <file>...
  file_to_c.py ship <name> move <x> <y> [--speed=<kn>]
  file_to_c.py ship shoot <x> <y>
  file_to_c.py mine (set|remove) <x> <y> [--moored | --drifting]
  file_to_c.py (-h | --help)
  file_to_c.py --version
  file_to_c.py (--path=<path>)...

Arguments:
  FILE        optional input file

Options:
  -h --help     Show this screen.
  --version     Show version.
  --speed=<kn>  Speed in knots [default: 10].
  --moored      Moored (anchored) mine.
  --drifting    Drifting mine.

"""

import sys
from docopt import docopt

def file_to_hex(path):
	res = ""
	if path:
 		with open(path,'rb') as f:
 			for item in f.read():
 				res += hex(ord(item))
 				res += ','
 			return res
 	else:
 		return 0

def save_file(content, file_name, save_path="result.txt", save_mod="C"):
 	with open(save_path, 'w+') as f:
 		if save_mod == "C":
 			file_head = "const static char " + file_name +"[] = {"
 			f.write(file_head)
 			f.write(content)
 			f.write("};")
 	return
 
if __name__ == "__main__":
 	# if not sys.argv[1]:
 	# 	paths = raw_input("请输入要转码的文件路径：")
 	# else:
 	# 	paths = sys.argv[1:]
 	# # print paths
 	# for path in paths:
 	# 	print 'path:',path
 	# 	content = file_to_hex(path)
 	# 	if content:
 	# 		save_path = path + "_result.txt"
 	# 		file_name = path.split('.')[0]
 	# 		print 'save_path:',save_path
 	# 		print 'file_name:',file_name
 	# 		save_file(content=content, file_name=file_name, save_path=save_path)
 	# 	# else:
 	# 	# 	print path," 路径无法解析"

	arguments = docopt(__doc__)
	# print arguments
	# print arguments.path
	print arguments.get('<file>')
