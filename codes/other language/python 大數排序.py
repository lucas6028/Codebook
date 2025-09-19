# 大數排序
# line one n : 多少數字
# next line : 依序輸入每行一個
# sort : sort + lambda
from sys import stdin

data = stdin.read().splitlines()

i = 0

while(i < len(data)):
    T = int(data[i].strip())
    i += 1
    temp = [int(data[i + index].strip()) for index in range(T)]
    i += T
    temp = sorted(temp, key = lambda x : (x))
    for ele in temp:
        print(ele)
