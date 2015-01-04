from sqlalchemy.orm import mapper, sessionmaker #sessionmaker() 函数是最常使用的创建最顶层可用于整个应用 Session 的方法,Session 管理着所有与数据库之间的会话
from datetime import datetime
from sqlalchemy import Table, MetaData, Column, ForeignKey, Integer, String, Unicode, DateTime #会SQL的人能理解这些函数吧?
engine = create_engine("sqlite:///tutorial.db", echo=True) #创建到数据库的连接,echo=True 表示用logging输出调试结果
metadata = MetaData() #跟踪表属性
user_table = Table( #创建一个表所需的信息:字段,表名等
'tf_user', metadata,
Column('id', Integer, primary_key=True),
Column('user_name', Unicode(16), unique=True, nullable=False),
Column('email_address', Unicode(255), unique=True, nullable=False),
Column('password', Unicode(40), nullable=False),
Column('first_name', Unicode(255), default=''),
Column('last_name', Unicode(255), default=''),
Column('created', DateTime, default=datetime.now))
metadata.create_all(engine)  #在数据库中生成表
class User(object): pass #创建一个映射类
mapper(User, user_table) #把表映射到类
Session = sessionmaker() #创建了一个自定义了的 Session类
Session.configure(bind=engine)  #将创建的数据库连接关联到这个session
session = Session()
u = User()
u.user_name='dongwm'
u.email_address='dongwm@dongwm.com'
u.password='testpass'  #给映射类添加以下必要的属性,因为上面创建表指定这几个字段不能为空
session.add(u)  #在session中添加内容
 
 
 
session.flush() #保存数据 session.commit() #数据库事务的提交,sisson自动过期而不需要关闭
 
 
query = session.query(User) #query() 简单的理解就是select() 的支持 ORM 的替代方法,
#可以接受任意组合的 class/column 表达式 print list(query) 
#列出所有user print query.get(1) 
#根据主键显示 print query.filter_by(user_name='dongwm').first() 
#类似于SQL的where,打印其中的第一个 u = query.filter_by(user_name='dongwm').first() u.password = 'newpass' 
#修改其密码字段 session.commit() #提交事务 print query.get(1).password #打印会出现新密码
 
 
for instance in session.query(User).order_by(User.id): 
#根据id字段排序,打印其中的用户名和邮箱地址 print instance.user_name, instance.email_address