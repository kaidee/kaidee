# import sqlite3
# conn = sqlite3.connect('DB\\userDB.db')
# conn.execute("create table if not exists address(id integer primary key autoincrement,name varchar(128),address varchar(128))")
# # conn.execute("insert into address(name,address)values('Susan','shenzhen')")
# # conn.execute("insert into address")
# # conn.execute("insert into address(name,address)values('Mathison','shenzhen')")
# conn.commit()
# cur = conn.cursor()
# cur.execute("select * from address")
# res = cur.fetchall()
# # print "address:", res
# for line in res:
# 	for f in line:
# 		print f
# cur.close()
# conn.close

import sqlite3
conn = sqlite3.connect(r'DB\mydatabase.sqlite')
conn.execute("create table if not exists lover(id integer primary key autoincrement,name varchar(128),friendship varchar(128))")
# conn.execute("insert into lover(name,friendship)values('Susan','girlfriend')")
conn.execute("insert into lover(name,friendship)values('CenYunyao','Nvshen')")
conn.commit()
cur = conn.cursor()
cur.execute("select * from lover")
res = cur.fetchall()
# print "address:", res
for line in res:
	for f in line:
		print f
cur.close()
conn.close