f = File.open("ex1", "r") 
f.each do |line|
	puts line
end
f.close