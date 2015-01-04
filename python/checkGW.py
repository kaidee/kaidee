# coding: utf-8
# Author:kaidee


import quanbugw as q
import xianyougw as x

# print q.quanbugw
# print x.xianyougw

n = []

for q in q.quanbugw:
	if q not in x.xianyougw:
		n.append(q)

# print n

s = ''
for ss in n:
	# print ss
	s += ''.join(ss)
	s += '\n'

# print s
with open("unusegw.txt", 'wb+') as f:
	f.write(s)