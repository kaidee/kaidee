require 'rubygems'
require 'mysql'

db =Mysql.connect('localhost','root','','test')

# db.query("INSERT INTO people(name,age)VALUES('ying',19)")
