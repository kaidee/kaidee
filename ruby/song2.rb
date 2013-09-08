class Song
	def initialize(name,artist,duration)
		@name = name
		@artist = artist
		@duration = duration
	end

	attr_reader :name, :artist, :duration

	attr_writer :duration

	def duration= (new_duration)
		@duration = new_duration
	end
end
song = Song.new("feng", "Jay", 244)
puts song.artist
puts song.name
puts song.duration
song.duration = 257
puts song.duration

# 照着书上敲的有错误 TNND