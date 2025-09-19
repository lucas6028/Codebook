# 讀取多行輸入
# line one first number
# line two operation
# line three second number
from sys import stdin

data = stdin.read().splitlines()

limit = len(data)
i = 0
while(i < limit):
    a = int(data[i].strip())
    i += 1
    operation = data[i].strip()
    i += 1
    b = int(data[i].strip())
    i += 1
    if(operation == '*'):
        print(int(a * b))
    else:
        print(int(a / b)) 

