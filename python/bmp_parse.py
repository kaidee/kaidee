# coding: utf-8

from PIL import Image
import glob, os, sys

'''
使用:
	把要处理的图片放入inputroot文件夹下
	执行 python bmp_parse.py
	
脚本会搜索当前路径下'inputroot'文件夹下所有在img_types类型的文件
并将在outputroot文件夹下生成黑白图及是否可通行的文本文件

从原始图片的0,0点开始 4*4 的像素格子里 黑色的像素点多于白色的像素点 就为不可通行

 第一行为 宽
 第二行为 高
  接着 就是地图信息 1 为可通行, 0为障碍
 例如:
	5
	5
	00000
	11110
	00010
	01111
	00000
'''

RECT_W = 8 #格子像素宽度
RECT_H = 8 #格子像素高度
img_types=[".png",".jpg",".bmp"] #要处理图片类型

# def is_blank(x, y):
	# return pix[x,y] >= 245

def createDirIfMissing(dir):
    if not os.path.exists(dir):
        os.makedirs(dir)

def main(inputroot, outputroot):
	for infile in glob.glob(inputroot + "/*"):
		file, ext = os.path.splitext(os.path.basename(infile))
		if ext.lower() in img_types:
			print infile
			im = Image.open(infile).convert("L")
			width, height = im.size
			im.save(outputroot + "/" + file + ext)
			print im.size
			print width, height
			# s = str(width) + '\n' + str(height)
			pix = im.load()

			def is_blank(x, y):
				return pix[x,y] >= 220

			# print pix[0,0]
			w = width % RECT_W #x轴余出部分
			h = height % RECT_H #y轴余出部分

			temp_height = height/RECT_H
			temp_width = width/RECT_W
			if w != 0 :
			    temp_width += 1
			if h != 0 :
			    temp_height +=  1

			s = str(temp_width) + '\n' + str(temp_height)

			for y in xrange(0, height, RECT_H):
				s += '\n'
				for x in xrange(0, width, RECT_W):
					k = 0
					if y <= height-h-RECT_H:
						if x <= width-w-RECT_W:
							for i in range(RECT_W):
								for j in range(RECT_H):
									if is_blank(x + i, y + j):
										k += 1
							if k >= RECT_W * RECT_H / 2:
								s += '1'
							else:
								s += '0'
						else:
							if w > 0: #右边余留部分
								for i in range(w):
									for j in range(RECT_H):
										if is_blank(x + i, y + j):
											k += 1
								if k >= w * RECT_H / 2:
									s += '1'
								else:
									s += '0'
					else: #下面余留部分
						if h > 0:
							if x <= width - w - RECT_W:
								for i in range(RECT_W):
									for j in range(h):
										if is_blank(x + i, y + j):
											k += 1
								if k >= RECT_W * h / 2:
									s += '1'
								else:
									s += '0'
							else: #右下角余留部分
								if w > 0:
									for i in range(w):
										for j in range(h):
											if is_blank(x + i, y + j):
												k += 1
									if k >= w * h / 2:
										s += '1'
									else:
										s += '0'
				# s += '\n'
			with open(outputroot + '/' + file + '.txt', 'wb+') as f:
				f.write(s)

if __name__ == '__main__':
	if len(sys.argv) > 2:
	    inputroot = sys.argv[1]
	    outputroot = sys.argv[2]
	else:
	    inputroot = 'inputroot'
	    outputroot = 'outputroot'

	createDirIfMissing(outputroot)

	main(inputroot, outputroot)