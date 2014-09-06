# coding: utf-8
# Author:kaidee

import EasyDialogs

lastcmd = ''
while True:
	lastcmd = EasyDialogs.AskString('输入', lastcmd)
	print lastcmd