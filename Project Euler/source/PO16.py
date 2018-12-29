numArray = [1]
DividedSum=0

def CalcCarry(numArray, ArrayLen) :
    for i in range(0, ArrayLen) :
        if (numArray[i] >= 10) :
            numArray[i] -= 10
            if (i == ArrayLen - 1) :
                numArray.append(1)
            else :
                numArray[i + 1] += 1
            
    return numArray

def Multiple(numArray) :
    ArrayLen = len(numArray)
    'print(numArray)'
    for i in range(0, ArrayLen) :
        numArray[i] *= 2
    numArray = CalcCarry(numArray, ArrayLen)

for i in range(0, 1000) :
    Multiple(numArray)

print(sum(numArray))
