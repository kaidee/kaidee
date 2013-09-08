#!/usr/bin/env ruby
# encoding: utf-8
#========================================================================
#   FileName: test3.rb
#     Author: Mathison
#      Email: vividlee2010@gmail.com
#   HomePage: http://mathison.sinaapp.com
# LastChange: 2012-07-18 14:02:21
#========================================================================
# x = system("date")
# x = `date`
# puts x

ls = IO.popen("ls","r+")
while line = ls.gets
	puts line
end
ls.close