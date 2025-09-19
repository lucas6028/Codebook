# 單行輸入
# format : n1, operation, n2
from sys import stdin

data = stdin.read().splitlines()

limit = len(data)
i = 0

while(i < limit):
    a, operation, b = map(str, data[i].split())
    a, b = int(a), int(b)
    i += 1
    if(operation == '+'):
        print(int(a + b))
    elif(operation == '-'):
        print(int(a - b))
    elif(operation == '*'):
        print(int(a * b))
    else:
        print(int(a // b))

