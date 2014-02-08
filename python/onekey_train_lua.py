#!/usr/bin/env python
# coding: utf-8

# import os
import os,fnmatch
import subprocess

input_dir = './'
file_type = '*.lua'

def out_lua_bytecode():

    for luafile in all_files(input_dir, file_type, single_level=False, yield_folders=True):
        # print "lua file: ", luafile
        out_file_name = luafile[:-4] + ".a"
        cmd = ['luajit', '-b', luafile, out_file_name]
        print 'cmd: ', cmd
        subprocess.check_call(cmd)

def del_lua_file():

    for luafile in all_files(input_dir, file_type, single_level=False, yield_folders=True):
        # print "lua file: ", luafile
        # out_file_name = luafile[:-4]
        cmd = ['rm', luafile]
        print 'cmd: ', cmd
        subprocess.check_call(cmd)

def rename_lua_file():
    for luafile in all_files(input_dir, '*.a', single_level=False, yield_folders=True):
        # print "lua file: ", luafile
        out_file_name = luafile[:-2] + ".lua"
        cmd = ['mv', luafile, out_file_name]
        print 'cmd: ', cmd
        subprocess.check_call(cmd)

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

    out_lua_bytecode()
    print '---------------------------------------------'
    del_lua_file()
    print '---------------------------------------------'
    rename_lua_file()





