from subprocess import *
#import subprocess
import time

sleep_time = 2

def main():
	web = 'qq.com'
	cmd = ['ping', web]
	# Popen(cmd)
	check_call(cmd)
	time.sleep(sleep_time)
	p = Popen(["ls", "-l"])

if __name__ == '__main__':
	Popen("date")
	# main()
