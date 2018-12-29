import math

def binary_search(data, target, low, high) :
    if low > high :
        return False
    else :
        mid = (low + high) // 2
        if target == data[mid] :
            return True
        elif target < data[mid] :
            return binary_search(data, target, low, mid -1)
        else :
            return binary_search(data, target, mid + 1, high)


ExArray = [1, ]
for i in range(2, 1001) :
    ExArray.append(i*i)

for i in range(0, 400) :
    for j in range(i+1, 400) :
        ExSum = ExArray[i] + ExArray[j]

        if (binary_search(ExArray, ExSum, 0, len(ExArray)-1)) :
           if( ( (i+1) + (j+1) + math.sqrt(ExSum) ) == 1000 ) :
                print( (i+1), (j+1), int(math.sqrt(ExSum)) )
                print((i+1) * (j+1) * int(math.sqrt(ExSum)) )



        
