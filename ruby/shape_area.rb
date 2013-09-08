class Shape
end

class Square <Shape
	def initialize(side_length)
		@side_length =side_length
		if defined?(@@number_of_squares)
			@@number_of_squares +=1
		else
			@@number_of_squares =1
		end
	end

	def area
		@side_length *@side_length

	end
	def Square.count
		@@number_of_squares
	end
end

my_square =Square.new(5)
puts my_square.area
puts Square.count
s =Square.new(6)
puts Square.count