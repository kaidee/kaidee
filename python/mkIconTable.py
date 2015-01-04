#!/usr/bin/env python
# coding: utf-8

# import os
import os,fnmatch
# import subprocess

input_dir = 'images/'
file_type = '*.png'

L = []
T = []

tab = '\t'
nl = '\n'
prefix = 'all_icons'

def main():
    for icon in all_files(input_dir, file_type, single_level=False, yield_folders=True):
        iconName = icon[8:]
        L.append(iconName)
        iconType = iconName.split('_')[1:2]
        if iconType not in T:
            T.append(iconType)
        # print iconType
        # name = iconName.split('_')[2:-1]
        # print icon

        # with open('all_images.lua', 'wb+') as f:
            # f.write(icon)

    data = 'all_icons = {'
    data = ''
    index = 100001
    data += prefix + ' = {}' + nl
    for icon_type in T:
        for icon_name in L:
            if icon_name.split('_')[1:2] == icon_type:
                data += prefix + '[' + str(index) + '] = {' + nl
                data += tab + 'name = "'+ ''.join(icon_name.split('_')[2:-1]) + '",' + nl
                data += tab + 'res = "' + str(icon_name) + '",' + nl
                data += tab + '}' + nl
                index += 1
        data += nl + nl

                # print icon_name

        # print '------------------'
        # print data

    # for x in range(1,len(T)):
    #     # print x, T[x]
    #     index = x*1000
    #     data += prefix+ ''.join(T[x]) + ' = {}' + nl
    #     for icon_name in L:
    #         if icon_name.split('_')[1:2] == T[x]:
    #             data += prefix + ''.join(T[x]) + '[' + str(index) + '] = {' + nl
    #             data += tab + 'name = "'+ ''.join(icon_name.split('_')[2:-1]) + '",' + nl
    #             data += tab + 'res = "' + str(icon_name) + '",' + nl
    #             data += tab + '}' + nl
    #             index += 1
    #     data += nl

        # print data

    # with open('icon_enums.lua', 'wb+') as f:
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
 





