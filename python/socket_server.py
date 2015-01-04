#coding:utf-8
# print '中文字符测试' #中文字符测试的注释
import socket
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
host = socket.gethostname()
port = 8000
s.bind((host,port))
s.listen(5)
while True:
	c,addr = s.accept()
	print 'conect seccess',addr
	c.send('恭喜啦，这一个已经连接成功了！')
	# c.send('yeah!!')
	c.close()