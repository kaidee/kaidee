# coding: utf-8
# Author:kaidee

from PIL import Image
import glob, os, sys

# inputroot = '../../../Pictures/3eb.jpg'
inputroot = '../../../Pictures/4X.png'




def main():
	im = Image.open(inputroot)
	width, height = im.size
	print width, height
	bands = im.getbands()
	# print bands
	data = im.getpixel((20, 20))
	print data
	pix = im.load()
	print pix[20,20]
	print(im.info)
	print(im.palette)


if __name__ == '__main__':
	main()