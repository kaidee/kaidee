class FirstClass:
	"""docstring for FirstClass"""
	def __init__(self, arg):
		# super(FirstClass, self).__init__()
		self.arg = arg
	def setdata(self, value):
		self.data = value
	def display(self):
		print self.arg

	z = 100

x = FirstClass("ling")
x.display()
y = 'hello'
# print locals()
for k, v in locals().items():
	print k, '=', v