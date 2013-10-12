import os

cmd = 'ls'
s = os.popen(cmd).read()
# s = os.system(cmd)
print s