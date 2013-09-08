class Person:
	"""docstring for Person"""
	def __init__(self, name, job=None, pay=0):
		self.name = name
		self.job = job
		self.pay = pay
	def lastName(self):
		return self.name.split()[-1]
	def giveRaise(self, percent):
		self.pay = int(self.pay * (1 + percent))
	def __str__(self):
		return '[Person: %s, %s]' % (self.name, self.pay)

class Manager(Person):
	"""docstring for Manager"""
	# def __init__(self, arg):
	# 	super(Manager, self).__init__()
	# 	self.arg = arg
	def giveRaise(self, percent, bonus=.10):
		# self.pay = int(self.pay * (1 + percent + bonus))
		self.pay = Person.giveRaise(self, percent + bonus)
		

if __name__ == '__main__':
	ling = Person('ling', pay=1000000)
	ling.giveRaise(.20)
	print ling.name,ling.pay,
	kaidee = Person('Mathison Lee', 'have no job')

	print kaidee.lastName(), kaidee.job

	print kaidee