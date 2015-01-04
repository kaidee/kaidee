#!/usr/bin/env python
# coding: utf-8

# import os
import os,fnmatch
# import subprocess

input_dir = '../client/resources/images/'
file_type = '*.png'

L = []
T = []
N = []

tab = '\t'
nl = '\n'
prefix = 'all_icons'

def main():
    for icon in all_files(input_dir, file_type, single_level=False, yield_folders=True):
        # icon_name = icon.split('/')[-1]
        icon_path = icon[len(input_dir):]
        L.append(icon_path)

    data = 'all_images = {}' + nl + nl
    idx = 1
    for path in L:
        icon_name = path.split('/')[-1]
        if icon_name not in N:
            N.append(icon_name)
        else:
            print icon_name, "  是重名文件!!!"
            # print "path: ", path
        data += 'all_images[' + str(idx) + '] = "' + ''.join(path[:]) + '"' + nl
        idx += 1



    # with open('allImagesList.lua', 'wb+') as f:
    #     f.write(data)




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
    main()
