# x = 'spam'
# y = 99
# z = ['eggs']
# print(x, y, z, sep='...', file=open('data.txt', 'w'))

import sys
print('RRRRRR')
# sys.stdout.write('Hello World!')
sys.stdout = open('data.txt', 'a')
print('ssss')