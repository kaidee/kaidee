#!/usr/bin/python
# coding: utf-8
import os
from collections import defaultdict
import traceback
import plistlib
import anim_pb2

def clean_path(f):
    if f.startswith('./') or f.startswith('.\\'):
        f = f[2:]
    return 'mc/'+f

animindex = defaultdict(lambda:defaultdict(list))
def animxml(f):
    try:
        d = plistlib.readPlist(f)
    except:
        print 'parse %s failed'%f
        traceback.print_exc()
        return
    for k in d['libItemDict']:
        animindex[clean_path(f)]['libItems'].append(k)

def anim(f, item):
    s = open(f, 'rb').read()
    anim = anim_pb2.Anim()
    anim.ParseFromString(s)
    item.name = clean_path(f)
    for sym in anim.symbols:
        item.symbols.append(sym.name)

plistindex = defaultdict(lambda:defaultdict(list))
def plist(f, framelist):
    try:
        d = plistlib.readPlist(f)
    except:
        print 'parse %s failed'%f
        traceback.print_exc()
        return
    for k, v in d['frames'].items():
        print(k)
        finfo = framelist.frames.add()
        finfo.name = k
        r = v['frame']
        origin, size = r[2:-2].split('},{')
        finfo.x, finfo.y = map(int, origin.split(','))
        finfo.w, finfo.h = map(int, size.split(','))
        finfo.rotated = v['rotated']
        
        filename = os.path.splitext(clean_path(f))[0]+'.png'
        if filename not in framelist.filenames:
            framelist.filenames.append(filename)
        
        finfo.filename = list(framelist.filenames).index(filename)

def main(d):
    # 递归目录
    import os

    oldpwd = os.getcwd()
    os.chdir(d)

    animidx = anim_pb2.AnimIndex()
    framelist = anim_pb2.FrameList()
    for root, dirs, files in os.walk('.'):
        for f in files:
            if f.endswith('.anim'):
                anim(os.path.join(root, f), animidx.anims.add())
            elif f.endswith('.plist'):
                plist(os.path.join(root, f), framelist)
            else:
                pass
    # output
    # open('anim.index', 'wb').write(animidx.SerializeToString())
    open('icons.index.pbb', 'wb').write(framelist.SerializeToString())

    os.chdir(oldpwd)

if __name__ == '__main__':
    import sys
    main('./')
