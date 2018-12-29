import math

def findDivisor(num) :
    count = 0
    for i in range(1, int(math.sqrt(num))+1) :
        if(num % i == 0) :
            if( i*i == num) :
                count+=1
            else :
                count+=2
    return count

'''print(findDivisor(21))'''

index = 1
triSum = 0

while(1) :
    triSum+=index
    count = findDivisor(triSum)
    'print(triSum ,"= " ,count)'
    if(count > 500) :
        print(triSum)
        break
    index+=1
