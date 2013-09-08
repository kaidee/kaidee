# coding:utf-8
# Author:kaidee

import os, sys

# from com.android.monkeyrunner import MonkeyRunner,MonkeyDevice,MonkeyImage

def antest():
	number = .01
	#等待主机与android设备连接
	device = MonkeyRunner.waitForConnection()
	MonkeyRunner.sleep(number)
	#杀掉待测程序，通常用于排除干扰
	device.shell('am force-stop com.alpha.lenovo.launcher')
	MonkeyRunner.sleep(number)
	#启动待测程序的主activity
	device.startActivity(component='com.alpha.lenovo.launcher/com.alpha.lenovo.launcher.AlphaLauncher')
	#开始发送按键
	MonkeyRunner.sleep(number)
	device.press('KEYCODE_MENU','DOWN_AND_UP')
	result = device.takeSnapshot()
	#文件将写入主机上,脚本所在目录
	result.writeToFile('./photo/pic001.png','png')

	MonkeyRunner.sleep(number)
	device.touch(350,730,'DOWN_AND_UP')
	result = device.takeSnapshot()
	#文件将写入主机上,脚本所在目录
	result.writeToFile('./photo/pic002.png','png')

	MonkeyRunner.sleep(number)
	device.press('KEYCODE_DPAD_DOWN','DOWN_AND_UP')
	MonkeyRunner.sleep(number)
	device.press("KEYCODE_DPAD_CENTER","DOWN_AND_UP")
	MonkeyRunner.sleep(number)
	device.press('KEYCODE_DPAD_DOWN','DOWN_AND_UP')
	MonkeyRunner.sleep(number)
	device.press("KEYCODE_DPAD_CENTER","DOWN_AND_UP")
	MonkeyRunner.sleep(number)

	#屏幕抓图
	result = device.takeSnapshot()
	#文件将写入主机上,脚本所在目录
	result.writeToFile('./photo/pic003.png','png')

	device.press('KEYCODE_HOME ','DOWN_AND_UP')
	MonkeyRunner.sleep(1.0)
	# print ()
def main(num=1):
	num = int(num)
	for x in xrange(0,num):
		# antest()
		print x

if __name__ == '__main__':
	num = int(sys.argv[1])
	main(num)
	# for x in xrange(1,3):
	# 	antest()
	# 	print (x)