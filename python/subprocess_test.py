# coding:utf-8
# Author:kaidee

# from subprocess import *
import subprocess
# import time

sleep_time = 2

def main():
	web = 'qq.com'
	cmd = ['ls', '-l']
	# Popen(cmd)
	out = subprocess.check_call(cmd, stdout=subprocess.PIPE)
	print
	# print out
	# time.sleep(sleep_time)
	# p = Popen(["ls", "-l"], stdout=PIPE) # 重定向输出
	# print out.stdout.read()

if __name__ == '__main__':
	# Popen("date")
	main()
