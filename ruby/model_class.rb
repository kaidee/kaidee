#!/usr/bin/env ruby
# encoding: utf-8

print "模块：", "\n\n"
puts Module.constants.sort.select {|x| eval(x.to_s).instance_of? Module}
puts

print "类：", "\n\n"
puts Module.constants.sort.select {|x|
	c = eval(x.to_s)
	c.is_a? Class and not c.ancestors.include? Exception
}
puts

print "异常类：", "\n\n"
puts Module.constants.sort.select {|x|
	c = eval(x.to_s)
	c.instance_of? Class and c.ancestors.include? Exception
}