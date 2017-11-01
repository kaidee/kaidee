#!/usr/bin/python
# -*- coding:utf-8 -*-

import sys
import gzip
from StringIO import StringIO

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print "Command line parameters error."
        print "Usage: UnGzip.py GzipFilePath ResFilePath"
        sys.exit(1)

    try:
        srcfile = open(sys.argv[1], "rb")
        srcdata = srcfile.read()
        buf = StringIO(srcdata)
        f = gzip.GzipFile(fileobj = buf)
        resdata = f.read()

        resfile = open(sys.argv[2], "wb")
        resfile.write(resdata)

        srcfile.close()
        resfile.close()
    except:
        import traceback
        import sys
        import StringIO
        f = StringIO.StringIO()
        traceback.print_exc(file=f)
        print f.getvalue()
        sys.exit(1)