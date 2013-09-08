def random
	(rand(26) + 65+32).chr
end

puts 97.chr
30.times{print random}
puts ''