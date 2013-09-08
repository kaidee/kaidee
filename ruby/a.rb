# text=''
# line_count = 0 
# File.open("text.txt").each do |line|
# 	line_count +=1
# 	text << line
# end
# puts "#{line_count} lines"
# word_count = text.split.length
# puts "#{word_count} word"
# sentence_count = text.split(/\.|\?|!/).length
# puts "#{sentence_count} sentence"
text = %q{Los Angeles has some of the nicest weather in the country.}
stop_words = %w{ the a by on for of are with just but and to the my I has some}

words = text.scan(/\w+/)
key_words = words.select{ |word| !stop_words.include?(word)}
puts key_words.join(' ')