#========================================================================
#   FileName: test.rb
#     Author: Mathison
#      Email: vividlee2010@gmail.com
#   HomePage: http://www.mathisonlee.com
# LastChange: 2012-05-06 14:18:41
#========================================================================
class Pet
	attr_accessor :name, :age, :gender, :color
end
class Cat <Pet
end

class Dog <Pet
	def bark
		puts "Woof!"
	end
end

class Snake <Pet
	attr_accessor :length
end

a_dog = Dog.new
puts a_dog.bark