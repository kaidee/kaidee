# coding:utf-8
# Author:kaidee

from Tkinter import *

def hello():
	print 'Hello Tkinter'

win = Tk()
win.title('Hello World!')
win.geometry('400x200')

btn = Button(win, text='click here', command=hello)
btn.pack(expand=YES)

mainloop()