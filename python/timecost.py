import time
def fast():
	time.sleep(0.001)
def slow():
	time.sleep(0.01)
def very_slow():
	for x in xrange(1,101):
		fast()
		slow()
	time.sleep(0.1)

def main():
	very_slow()
	# very_slow()

if __name__ == '__main__':
	main()