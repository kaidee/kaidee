from com.android.monkeyrunner import MonkeyRunner, MonkeyDevice, MonkeyImage
import time

sleeptime = 0.01

def drag(pos, dir):
	tx = pos[0]
	ty = pos[1]
	if dir == "up":
		ty -= 100
	if dir == "down":
		ty += 100
	if dir == "left":
		tx -= 100
	if dir == "right":
		tx += 100
	device.drag(pos, (tx, ty), 0, 1)

device = MonkeyRunner.waitForConnection()

def capToFile():
	screen = device.takeSnapshot()
	name = str(int(time.time()))
	screen.writeToFile('img/' + name + ".png", "png")

def getNodePos(x, y):
	width = 108
	height = 108
	return (80+(x*width),280+(y*height))

# crazy monkey(s)
def monkeyrun():
	for y in xrange(2, 7, 2):
		for x in xrange(0, 8):
			drag(getNodePos(x, y), "up")
	time.sleep(sleeptime)
	
	for y in xrange(1, 6, 2):
		for x in xrange(0, 8):
			drag(getNodePos(x, y), "up")
	time.sleep(sleeptime)
	
	for x in xrange(0, 5, 2):
		for y in xrange(0, 8):
			drag(getNodePos(x, y), "right")
	time.sleep(sleeptime)
	
	for x in xrange(1, 6, 2):
		for y in xrange(0, 8):
			drag(getNodePos(x, y), "right")
	time.sleep(sleeptime)
	
	for y in xrange(0, 5, 2):
		for x in xrange(0, 8):
			drag(getNodePos(x, y), "down")
	time.sleep(sleeptime)
	
	for y in xrange(1, 6, 2):
		for x in xrange(0, 8):
			drag(getNodePos(x, y), "down")
	time.sleep(sleeptime)
	
	for x in xrange(2, 7, 2):
		for y in xrange(0, 8):
			drag(getNodePos(x, y), "left")
	time.sleep(sleeptime)
	
	for x in xrange(1, 6, 2):
		for y in xrange(0, 8):
			drag(getNodePos(x, y), "left")
	time.sleep(sleeptime)

def getpuzzle():
	screen = device.takeSnapshot()
	capToFile()
	puzzle = []
	for y in xrange(0,7):
		line = []
		for x in xrange(0,7):
			line.append(screen.getRawPixelInt(getNodePos(x,y)[0], getNodePos(x,y)[1]))
		puzzle.append(line)
		# print 'puzzle:', puzzle
		# with open('puzzle.txt', 'wb') as f:
			# f.write(str(puzzle))
	return puzzle

# lazy one
def trainedmonkey():
	x = 0
	y = 0
	do = True
	pr = True
	puzzle = getpuzzle()
	
	while (x < 7):
		while (y < 7):
			################################
			#  if match patterns, drag up  #
			################################
			
			# o o
			#     0
			if ((y > 0 and x > 1 and
				 puzzle[y][x] == puzzle[y-1][x-1] and
				 puzzle[y][x] == puzzle[y-1][x-2]) or
				# o   o
				#   0
				(y > 0 and x > 0 and x < 6 and
				 puzzle[y][x] == puzzle[y-1][x-1] and
				 puzzle[y][x] == puzzle[y-1][x+1]) or
				#   o o
				# 0
				(y > 0 and x < 5 and
				 puzzle[y][x] == puzzle[y-1][x+1] and
				 puzzle[y][x] == puzzle[y-1][x+2]) or
				# o
				# o
				#
				# 0
				(y > 2 and
				 puzzle[y][x] == puzzle[y-2][x] and
				 puzzle[y][x] == puzzle[y-3][x])):
					
					if pr: print x, y, "up"
					if do: drag(getNodePos(x, y), "up")
					return
			
			###################################
			#  if match patterns, drag right  #
			###################################
			
			#   o
			#   o
			# 0
			if ((y > 1 and x < 6 and
				 puzzle[y][x] == puzzle[y-1][x+1] and
				 puzzle[y][x] == puzzle[y-2][x+1]) or
				#   o
				# 0
				#   o
				(y > 0 and y < 6 and x < 6 and
				 puzzle[y][x] == puzzle[y-1][x+1] and
				 puzzle[y][x] == puzzle[y+1][x+1]) or
				# 0
				#   o
				#   o
				(y < 5 and x < 6 and
				 puzzle[y][x] == puzzle[y+1][x+1] and
				 puzzle[y][x] == puzzle[y+2][x+1]) or
				# 0   o o
				(x < 4 and
				 puzzle[y][x] == puzzle[y][x+2] and
				 puzzle[y][x] == puzzle[y][x+3])):
					
					if pr: print x, y, "right"
					if do: drag(getNodePos(x, y), "right")
					return
			
			##################################
			#  if match patterns, drag down  #
			##################################
			
			# 0
			#   o o
			if ((y < 6 and x < 5 and
				 puzzle[y][x] == puzzle[y+1][x+1] and
				 puzzle[y][x] == puzzle[y+1][x+2]) or
				#   0
				# o   o
				(y < 6 and x > 0 and x < 6 and
				 puzzle[y][x] == puzzle[y+1][x+1] and
				 puzzle[y][x] == puzzle[y+1][x-1]) or
				#     0
				# o o
				(y < 6 and x > 1 and
				 puzzle[y][x] == puzzle[y+1][x-1] and
				 puzzle[y][x] == puzzle[y+1][x-2]) or
				# 0
				#
				# o
				# o
				(y < 4 and
				 puzzle[y][x] == puzzle[y+2][x] and
				 puzzle[y][x] == puzzle[y+3][x])):
					
					if pr: print x, y, "down"
					if do: drag(getNodePos(x, y), "down")
					return
			
			##################################
			#  if match patterns, drag left  #
			##################################
			
			#   0
			# o
			# o
			if ((y < 5 and x > 0 and
				 puzzle[y][x] == puzzle[y+1][x-1] and
				 puzzle[y][x] == puzzle[y+2][x-1]) or
				# o
				#   0
				# o
				(y > 0 and y < 6 and x > 0 and
				 puzzle[y][x] == puzzle[y-1][x-1] and
				 puzzle[y][x] == puzzle[y+1][x-1]) or
				# o
				# o
				#   0
				(y > 1 and x > 0 and
				 puzzle[y][x] == puzzle[y-1][x-1] and
				 puzzle[y][x] == puzzle[y-2][x-1]) or
				# o o   0
				(x > 2 and
				 puzzle[y][x] == puzzle[y][x-2] and
				 puzzle[y][x] == puzzle[y][x-3])):
					
					if pr: print x, y, "left"
					if do: drag(getNodePos(x, y), "left")
					return
			
			y = y + 1
		x = x + 1
		y = 0

def testdrag(x,y):
	drag(getNodePos(x, y), "up")
	time.sleep(0.5)
	drag(getNodePos(x, y), "right")
	time.sleep(0.5)
	drag(getNodePos(x, y), "down")
	time.sleep(0.5)
	drag(getNodePos(x, y), "left")
	time.sleep(0.5)

if __name__ == '__main__':
	while True:
		# trainedmonkey()
		# getpuzzle()
		capToFile()
		#testdrag(100, 100)
		time.sleep(1)
