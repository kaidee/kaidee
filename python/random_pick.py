#encoding=utf-8

# print '中国'

#以指定的概率获取元素 以一个列表为基准概率，从一个列表中随机获取元素

import random

def random_pick(some_list, probabilities):
    x = random.uniform(0,1)
    print x
    cumulative_probability = 0.0
    for item, item_probability in zip(some_list, probabilities):
        cumulative_probability += item_probability
        print cumulative_probability
        if x < cumulative_probability:break
    return item

some_list = [1,2,3,4]
probabilities = [0.2,0.1,0.6,0.1]

# print random_pick(some_list,probabilities)

for x in xrange(1,30):
    print random_pick(some_list,probabilities),
    
print '------------------------'

#根据权重来获取 核心在于权重乘以 就相当于次数

def random_pick_odd(some_list, odds):
    print 'table2'
    table = [z for x,y in zip(some_list,odds) for z in [x] * y] 
    print table
    return random.choice(table)
    
some_list = [1,2,3,4]
odds=[3,1,4,2]

print random_pick_odd(some_list,odds)


#for item in random_picks()


# print random.random()