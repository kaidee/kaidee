#!/usr/bin/env ruby
def random
	rand(Time.new.to_i)
end

# puts random
100.times{print random.to_s + " "}