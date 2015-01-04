def to2(n):
	l = []
	while n != 0:
		(n, temp) = divmod(n, 2)
		l.append(temp)
	result = ''
	while len(l) > 0:
		result += str(l.pop())
	return result

print to2(100)