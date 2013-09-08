# class BadDataException < RuntimeError
# end

# class Person
# 	def initialize(name)
# 		raise BadDataException, "No name present" if name.empty?
# 	end
# end
 
# m = Person.new('')

# begin
# 	puts 10 / 0
# rescue => e
# 	puts e.class
# 	puts "You caused an error!"
# end

catch(:finish) do
	1000.times do 
		x = rand(1000)
		throw :finish if x==123
	end
	puts "Generated 1000 random numbers without generating 123!"
end