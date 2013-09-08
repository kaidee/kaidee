class WordPlay
end

class String
	def sentences
		gsub(/\n|\r/,' ').split(/\.\s*/)
	end

	def words
		scan(/\w[\w\'\-]*/)
	end
end

# puts %q{Hello.aaaa.bbbb.mm gg hi}.words.inspect

hot_words =%w{test ruby}
my_string ="This is a test.Dull sentence here.Ruby is great.So is cake."
my_string.sentences.find_all do |s|
	s.downcase.words.any?{|word|hot_words.include?(word)}
end

def self.best_sentence(sentences,desired_words)
	ranked_sentences = sentences.sort_by do |s|
		s.words.length - (s.downcase.words - desired_words).length
	end

	ranked_sentences.last
end

weiwancheng