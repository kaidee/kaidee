require 'yaml'
class Person
	attr_accessor :name, :age
end

mathison =Person.new
mathison.name ="Mathison Lee"
mathison.age =21

ling =Person.new
ling.name ="Ling Zhang"
ling.age =20

test_data =[mathison, ling]

puts YAML::dump(test_data)