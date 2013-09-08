class Song
	def initialize(name,artist,duration)
		@name = name
		@artist = artist
		@duration = duration
		
	end
end
class Song
	def to_s
		"Song: #@name--#{@artist} (#{@duration})"
		
	end
end
song = Song.new("Bicyclops","Fleck",260)
# puts song.inspect
puts song.to_s

class KaraokeSong < Song
	def initialize(name,artist,duration,lyrics)
		super(name,artist,duration)
		@lyrics = lyrics
	end
	def to_s
		super + " [#{@lyrics}]"
		
	end
end

song1 = KaraokeSong.new("My Way","Sinatra",225,"And now,the...")
puts song1.to_s