#!/usr/bin/env python
# coding: utf-8

# import os
import os,fnmatch
from PIL import Image
# import subprocess

input_dir = 'inputroot/'
output_dir = 'outputroot'
# input_img = '程序效果图/XGT_角色选择.png'
input_img = '1_1.png'
file_type = '*.png'
# input_dir = '../python/inputroot/'


def main():
    for img in all_files(input_dir, file_type, single_level=False, yield_folders=True):
        # print img
        new_name = ''.join(img[len(input_dir):-4]) + '.jpg'
        new_path = os.path.join(output_dir, new_name)
        # print new_path
        im = Image.open(img)
        im.save(new_path, quality=85)

    # im = Image.open(input_img)
    # im.save("quality100.jpg", quality=100)
    # im.save("quality95.jpg", quality=95)
    # im.save("quality90.jpg", quality=90)
    # im.save("quality85.jpg", quality=85)
    # im.save("quality80.jpg", quality=80)
    # im.save("quality75.jpg", quality=75)
    # im.save("quality75.jpg", quality=75)
    # im.save("quality30.jpg", quality=30)
    # im.save("quality50.jpg", quality=50)
    # im.save("quality60.jpg", quality=60)
    # im.save("quality70.jpg", quality=70)






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
    print "Done...."