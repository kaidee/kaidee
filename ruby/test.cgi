#!/usr/bin/ruby


# puts "Content-type: text/html\n\n"
# puts "<html><body>This is a test</body></html>"

require 'cgi'
cgi = CGI.new

text = cgi['text']

puts cgi.header
puts "<html><body>#{text.reverse}</body></html>"