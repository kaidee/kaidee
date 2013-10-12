from subprocess import *

print 'open subprocess'
p = Popen("date")
print 'sub process running'
r = p.wait()
print 'end of sub process ', r , type(r)

