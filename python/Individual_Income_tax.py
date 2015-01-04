# coding: utf-8
# Author: kaidee

def calcTax(income, duty_free, Start = 3500):
    # 
    sum = [1500, 4500, 9000, 35000, 55000, 80000]
    # 
    rate = [3, 10, 20, 25, 30, 35, 45]
    # 
    tax = [0, 105, 555, 1005, 2755, 5505, 13505]

    dSum = income - duty_free - Start
    for i in range(len(sum)):
        if dSum < sum[i]:
            break
    if i == len(sum):
        i = len(sum) - 1
    dTax = dSum * float(rate[i]) / 100.0 - tax[i] 
    if dTax < 0:
        dTax = 0
    return (dTax, income - duty_free - dTax)

def get_input(msg, default):
	while True:
		try:
			line = raw_input(msg)
			if not line and default is not None:
				return default
			i = float(line)
			if i < 0:
				print("输入必须大于零")
			else:
				return i
		except ValueError as err:
			print(err)


if __name__ == '__main__':
	while True:
		income = get_input("请输入总月收入（默认为零）：", 0)
		duty_free = get_input("请输入总免税额（默认为零）：", 0)
		dTax, dSum = calcTax(income, duty_free)
		print "您这个月要交%s税，税后收入为：%s" % (dTax, dSum)
		print
