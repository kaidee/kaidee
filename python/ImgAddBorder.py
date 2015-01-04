# coding: utf-8
# Author:kaidee

from PIL import Image
import glob, os, sys

# inputroot = '../../../Pictures/3eb.jpg'
# inputroot = '../../../Pictures/4X.png'
inputroot = 'inputroot'
BORDER = 20

class AddBorder(object):
	"""docstring for AddBorder"""
	def __init__(self, arg):
		super(AddBorder, self).__init__()
		self.arg = arg

	def readImageContent(self, image):
		im = Image.open(image, 'r')
		


def main():
	im = Image.open(inputroot)
	width, height = im.size
	print width, height
	# print bands
	data = im.getpixel((20, 20))
	print data
	pix = im.load()
	print pix[20,20]
	print(im.info)
	print(im.palette)


if __name__ == '__main__':
	main()