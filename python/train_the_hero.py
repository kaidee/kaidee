#!/usr/bin/env python
# coding: utf-8

# import os
import os,fnmatch
from PIL import Image

input_dir = 'role'
output_dir = 'output'
file_type = '*.png'

def create_dir_if_missing(dir):
	if not os.path.exists(dir):
		os.mkdir(dir)

def get_full_hero_name(p_path, files):
	# basename = os.path.basename(files)
	# hero_name = files.split('/')[1]
	# print 'hero_name:', hero_name
	full_hero_name = files[files.find('/')+1:].replace('/', '_')
	# full_hero_name = '_'.join(full_hero_name.split('_')[1:])

	print 'full_hero_name:', full_hero_name
	return full_hero_name

def train():
	for dir_item in os.listdir(input_dir):

		if dir_item.endswith('.svn') or dir_item.endswith('.git') or dir_item.endswith('.DS_Store'):
			continue

		# print 'dir_item:', dir_item
		hero_path = os.path.join(input_dir, dir_item)
		if os.path.isdir(os.path.join(input_dir, dir_item)):
			print 'dir_item:', dir_item
			save_path = os.path.join(output_dir, dir_item)
			create_dir_if_missing(save_path)

			print 'hero_path:', hero_path
			for files in all_files(hero_path, file_type, yield_folders=True):
				print 'files', files
				full_hero_name = get_full_hero_name(dir_item, files)
				img = Image.open(files)
				img.save(os.path.join(save_path, full_hero_name))


def all_files(root,patterns='*',single_level=False,yield_folders=False):
    patterns = patterns.split(';')
    # print root
    for path,subdirs,files in os.walk(root):
        if yield_folders:
            files.extend(subdirs)
        files.sort()
        for name in files:
            for pattern in patterns:
                if fnmatch.fnmatch(name,pattern):
                    yield os.path.join(path,name)
                    break
        if single_level:
            break
 
if __name__ == '__main__':
	create_dir_if_missing(output_dir)

	train()