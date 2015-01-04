#!/usr/bin/env python
# coding: utf-8
# Author:kaidee

# 统计代码行数

import os,fnmatch
import time

# 需要统计的根路径
input_dir = '.'
# 文件后缀类型，以';'分隔
# file_type = '*.*'
file_type = '*.h;*.cpp;*.lua;*.py;*.c;*.cc;'
# 忽略路径
ignor_dir = '.git'

def main():
    line_count = 0
    start_time = time.time()
    for file in all_files(input_dir, file_type, single_level=False, yield_folders=True):
        if ignor_dir in file:
            print file
            continue
        line_count += getLineCount(file)

    print
    print "This dir has ", line_count, "line codes"
    print time.time() - start_time ,"seconds costed"


def getLineCount(filename):
    with open(filename, "r") as f:
        return sum(line.count("\n") for line in block(f))

def block(file, size=65536):
    while True:
        nb = file.read(size)
        if not nb:
            break
        yield nb

def all_files(root,patterns='*',single_level=False,yield_folders=False):
    patterns = patterns.split(';')
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
    main()
