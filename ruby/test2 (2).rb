# f = File.new("logfile.txt","r+")
# puts f.gets
# f.puts "This is a test"
# puts f.gets
# # f.puts Time.now
# f.close

# File.rename("test.txt","logfile.txt")
# File.join('full','path','here','filename.txt')


# f.seek(-5,IO::SEEK_END)
# f.putc "X"
# f.close

# puts File.mtime("logfile.txt")
# puts File.size("text.txt")

require 'csv'
p CSV.read('text.txt')
thank = p.find{ |p| p[0][0] =~/thank/ }
puts thank.inspect