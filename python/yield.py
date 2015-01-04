def gensquares(n):
	for i in range(n):
		yield i**2

# for i in gensquares(5):
# 	print i, ': ',

x = gensquares(4)
print next(x)
print x.next()

def gen():
	for i in xrange(1,10):
		x = yield i
		print x

# G = gen()
# print next(G)
# print G.send(99)
# print G.send(99)
# print next(G)