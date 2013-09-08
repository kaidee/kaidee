#!/usr/bin/env ruby
# encoding: utf-8
#========================================================================
#   FileName: test6.rb
#     Author: Mathison
#      Email: vividlee2010@gmail.com
#   HomePage: http://www.mathisonlee.com
# LastChange: 2012-05-05 23:00:00
#========================================================================

# person = { :name => "Fred", :age => 20, :gender => :male}
# puts person.inspect	
a = "`size` bigint(64) unsigned NOT NULL COMMENT '附近大小'"
w = a.scan(/`(\w+)`|'(.+)'/)
puts w