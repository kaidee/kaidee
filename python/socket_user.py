#coding:utf-8
from socket import *
s = socket()
host = gethostname()
port = 8000
s.connect((host,port))
# s=s.decode('utf-8').encode('utf-8')
print s.recv(1024)
s.close()