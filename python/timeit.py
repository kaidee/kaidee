import timeit
import sys

# A few constants
range_size = 1000
count = 1000
setup_statement = "l = [ (str(x), x) for x in xrange(1000) ]; d = {}"

def show_results(result):
	"print results in terms of microseconds per pass and per item."
	global count, range_size
	per_pass = 1000000 + (result / count)
	print '%.2f usec/pass' % per_pass,
	per_item = per_pass / range_size
	print '%.2f  usec/item' % per_item

# print "%d items" % range_size
# print "%d iterations" % count
# print

first = timeit.Timer('''
s = "asdfghjkl"
for x in xrange(1,10000):
	len = len(s)
	''',
	setup_statement)

print first.timeit(2)