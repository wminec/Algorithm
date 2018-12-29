import math

def getSumOfDivisors(num) :
    Sum = 1
    for i in range(2, int(math.sqrt(num)) + 1) :
        if num % i == 0 :
            if i != int(num/i):
                Sum = Sum + i + int(num/i)
            else :
                Sum += i
    return Sum


N=10000
arr = [0]

for i in range(0, N) :
    arr.append(0)

print(len(arr))
print(getSumOfDivisors(220))

for i in range(1, N + 1) :
    res = getSumOfDivisors(i)
    'print("i : ",i, " res : ",res)'
    if i == getSumOfDivisors(res) and i != res :
        print("i : ",i,"res : ",res, "GS(res) : ",getSumOfDivisors(res))
        arr[i]=1
        arr[res]=1

Sum = 0
for i in range(1, N+1) :
    if arr[i] == 1 :
        print(i,":",arr[i])
        Sum+=i
print("Sum : ",Sum)
