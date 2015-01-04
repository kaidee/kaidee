#!/usr/bin/env python
# coding: utf-8
# author: kaidee

# 重命名文件名

# import os
import os,fnmatch
# from PIL import Image

input_dir = 'boss'
output_dir = 'output'
file_type = '*.png'

def train():
    for dir_item in os.listdir(input_dir):

        if dir_item.endswith('.svn') or dir_item.endswith('.git') or dir_item.endswith('.DS_Store'):
            continue

        for files in all_files(input_dir, file_type, yield_folders=True):
            # print 'files', files
            new_file_name = files.replace('boss', 'bs')
            print new_file_name
            os.renames(files, new_file_name)

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
    # create_dir_if_missing(output_dir)

    train()