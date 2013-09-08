class Song
		def initialize(name,artist,duration)
		@name = name
		@artist = artist
		@duration = duration
		
	end
	def name
		@name
	end
	def artist
		@artist
	end
	def duration
		@duration
	end
end
song = Song.new("feng", "Jay", 244)
puts song.artist
puts song.name
puts song.duration