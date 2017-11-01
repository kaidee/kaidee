#!/usr/bin/env python
# coding: utf-8
# Author:kaidee

'''
(235) 豹子， 同花顺， 同花， 顺子， 对子 
'''
# from multiprocessing.dummy import Pool as ThreadPool
# from multiprocessing import Pool

huasezhi = (0, 1, 2, 3)
paizhizhi = (2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14)
ersanwu = [ (x<<4) + y for x in huasezhi for y in [2, 3, 5] ]
ersanwu = set(ersanwu)
index = {}
# print 'ersanwu: ', ersanwu

def huase(n):
	return n>>4

def paizhi(n):
	return n - ((n>>4)<<4)

def is_same_color(a, b):
	return huase(a) == huase(b)

def is_same_paizhi(a, b):
	return paizhi(a) == paizhi(b)

def is_canbe_shunzi(a, b):
	return abs(paizhi(a) - paizhi(b)) <= 2

def cmp_func(x, y):
	if paizhi(x[1]) == paizhi(y[1]):
		return cmp(huase(x[1]), huase(y[1]))
	else:
		return cmp(paizhi(y[1]), paizhi(x[1]))

def calc_huangxiangpai(dipai, shoupai):
	if is_same_paizhi(dipai, shoupai):
		return paizhi(dipai)
	elif is_same_color(dipai, shoupai) and is_canbe_shunzi(dipai, shoupai):
		if abs(paizhi(dipai) - paizhi(shoupai)) == 1:
			if max(paizhi(dipai), paizhi(shoupai)) >=14:
				return min(dipai, shoupai) - 1
			else:
				return max(dipai, shoupai) + 1
		elif abs(paizhi(dipai) - paizhi(shoupai)) == 2:
			return max(dipai, shoupai) - 1
		else:
			print '计算同花顺出错！'
	elif is_same_color(dipai, shoupai):
		return 14 + ((dipai>>4)<<4)
	elif is_canbe_shunzi(dipai, shoupai):
		if abs(paizhi(dipai) - paizhi(shoupai)) == 1:
			if max(paizhi(dipai), paizhi(shoupai)) >=14:
				return min(paizhi(dipai), paizhi(shoupai)) - 1
			else:
				return max(paizhi(dipai), paizhi(shoupai)) + 1
		elif abs(paizhi(dipai) - paizhi(shoupai)) == 2:
			return max(paizhi(dipai), paizhi(shoupai)) - 1
		else:
			print '计算顺子出错！'
	else:
		if paizhi(dipai) > paizhi(shoupai):
			return paizhi(dipai)
		else:
			return paizhi(shoupai)

def generate_index():
	''' 生成幻想牌索引 '''
	paixing = []
	for x in huasezhi:
		for y in paizhizhi:
			paixing.append((x<<4) + y)
		
	index_content = {}
	for dipai_idx in paixing:
		index_content[dipai_idx] = {}
		for shoupai_idx in paixing:
			huanxiangpai = calc_huangxiangpai(dipai_idx, shoupai_idx)
			index_content[dipai_idx][shoupai_idx] = huanxiangpai

	return index_content

##----------------------------------------------------------------------

def find_the_biggest(dipai, wanjiapai):
	dipaizhi = paizhi(dipai)
	wanjiapaizhi = [paizhi(x) for x in wanjiapai]
	# print 'dipaizhi: ', dipaizhi
	# print 'wanjiapaizhi: ', wanjiapaizhi
	if dipaizhi in wanjiapaizhi:
		''' 能出豹子 '''
		tmp = filter(lambda x: x != dipaizhi, [2,3,5])
		if dipaizhi in ersanwu and tmp[0] in wanjiapaizhi or tmp[1] in wanjiapaizhi:
			''' 能出 235 '''
			num235_pos = 0
			num235pai = 96
			for (offset, pai) in enumerate(wanjiapai):
				if paizhi(pai) == dipaizhi:
					if huase(pai) < huase(num235pai):
						num235_pos = offset
						num235pai = pai
				elif paizhi(pai) > paizhi(num235pai):
					num235_pos = offset
					num235pai = pai
					
			return num235_pos, True

		else:
			baozi_pos = 0
			baozipai = 100
			for (offset, pai) in enumerate(wanjiapai):
				if paizhi(pai) == dipaizhi:
					if huase(pai) < huase(baozipai):
						baozi_pos = offset
						baozipai = pai
			return baozi_pos, False
	else:
		tonghua = []
		shunzi = []
		tonghuashun = []
		qita = []
		for (offset, pai) in enumerate(wanjiapai):
			if is_same_color(dipai, pai):
				tonghua.append((offset, pai))
			if is_canbe_shunzi(dipai, pai):
				shunzi.append((offset, pai))
			else:
				qita.append((offset, pai))

		tonghuashun = filter(lambda x: x in shunzi, tonghua)
		if tonghuashun:
			tonghuashun.sort(cmp=cmp_func)
			return tonghuashun[0][0], False
		elif tonghua:
			tonghua.sort(cmp=cmp_func)
			return tonghua[0][0], False
		elif shunzi:
			shunzi.sort(cmp=cmp_func)
			return shunzi[0][0], False
		else:
			qita.sort(cmp=cmp_func)
			return qita[0][0], False

def calculate(data):
	''' 计算每行数据 '''
	result = []
	dipai = data[0]
	wanjiapai = data[1:]
	biggest_pos, is_235 = find_the_biggest(dipai, wanjiapai)
	result.append(biggest_pos + 1)
	if not is_235:
		for pai in wanjiapai:
			result.append(index[dipai][pai])
	else:
		for pai in wanjiapai:
			if paizhi(dipai) != paizhi(pai) and pai in ersanwu:
				huanxiangpai = filter(lambda x: x != paizhi(dipai) and x != paizhi(pai), [2,3,5])[0]
				if huase(dipai) == huase(pai) == 0:
					result.append(huanxiangpai + (1<<4))
				else:
					result.append(huanxiangpai)
			else:
				result.append(index[dipai][pai])

	return result

def readfile():
	data = []
	hangshu = 0
	with open('input.txt', 'r') as f:
		all_data = f.readlines()
		hangshu = int(all_data[0])
		all_data = all_data[1:]
		for (offset, item) in enumerate(all_data):
			d = item.split()
			data.append(map(int, d))
	return data

def dumpfiles(data):
	result_str = ''
	for rst in data:
		result_str += ' '.join(map(str, rst)) + '\n'

	with open('output.txt', 'w+') as f:
		f.write(result_str)

def main():
	global index
	index = generate_index()
	data = readfile()
	# print 'data: ', data
	# pool = ThreadPool()
	# # pool = Pool()
	# results = pool.map(calculate, data)
	# pool.close()
	# pool.join()

	results = map(calculate, data)

	# calculate([24, 30, 42, 51]) #1 30 9 8    1 29 9 8
	# calculate([40, 46, 51, 43]) #1 46 8 46    1 45 8 46

	# print results

	# results = []
	# for item in data:
	# 	result = calculate(item)
	# 	results.append(result)

	dumpfiles(results)

	# print 'index: ', index[24][21]

if __name__ == '__main__':
	main()
	
