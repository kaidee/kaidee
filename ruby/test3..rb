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
	# def play
	# 	@play = @play+1
	# 	# @@play += 1
	# 	puts "This song:#{@plays} plays. Total #{@@plays} plays"
	# end
end

class MyLogger
	private_class_method :new
	@@logger = nil
	def MyLogger.creat
		@@logger = new unless @@logger
		@@logger
	end
end
# song = Song.new("when she was gone", "JJ", 260)
# puts song.name , song.artist, song.duration

puts MyLogger.creat.object_id