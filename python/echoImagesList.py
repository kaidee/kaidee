#!/usr/bin/env python
# coding: utf-8

# import os
import os,fnmatch
import subprocess as SP

# cmd2 = ['mv', unzipped, unzipped_dir]
# subprocess.check_call(cmd2)

# input_dir = '../../android/client/resources/images/'
input_dir = '../client/resources/images/task/'
# input_dir = '../python/inputroot/'
file_type = '*.png'

py_head = '''#!/usr/bin/env python
# coding: utf-8'''

L = []
T = []

tab = '\t'
nl = '\n'
prefix = 'all_icons'

def main():
    for icon_path in all_files(input_dir, file_type, single_level=False, yield_folders=True):
        L.append(icon_path[len(input_dir):])

    pyData = py_head + nl + nl
    pyData += 'all_images = {' + nl
    lua_data = 'all_images = {' + nl
    idx = 1
    for i in xrange(0,len(L)):
        # print L[i]
        icon = L[i]
        icon_name = os.path.basename(icon)
        old_icon_path = input_dir + icon
        new_icon_name = "icon_" + str(i) + ".png"
        new_icon_path = old_icon_path.replace(icon_name, new_icon_name)
        new_icon = new_icon_path[len(input_dir):]

        # 重命名图片
        # os.rename(old_icon_path, new_icon_path)

        pyData += '"' + ''.join(icon_name[:-4]) + '" : "'  + ''.join(new_icon) + '",' + nl
        # lua_data += '["' + ''.join(icon_name[:-4]) + '"] = "'  + ''.join(new_icon) + '",' + nl
        lua_data += '["' + ''.join(icon_name[:-4]) + '"] = "'  +'task/' +  icon_name + '",' + nl
        idx += 1

    lua_data += "}"
    pyData += "}"




    with open('allImagesList.lua', 'wb+') as f:
        f.write(lua_data)
    with open('allImagesList.py', 'wb+') as f:
        f.write(pyData)

    print "Done..."



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
 





