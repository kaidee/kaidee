class Song
	@@plays = 0
	def initialize(name, artist, duration)
		@name = name
		@artist = artist
		@duration = duration
		@plays = 0
	end
	attr_reader :name, :artist, :duration

	attr_writer :duration
	def play
		@play += 1
	end

	# def play
	# 	@play = @play+1
	# 	# @@play += 1
	# 	puts "This song:#{@plays} plays. Total #{@@plays} plays"
	# end
end
# @plays = 0
# song = Song.new("when she was gone", "JJ", 260)
# puts song.name , song.artist, song.duration
# song.duration = 257
# puts song.duration
s1 = Song.new("Song1", "Artist1",234)
s2 = Song.new("Song2", "Artist2",345)
s1.play 
s2.play
s1.play 
s2.play 
				# Have some error