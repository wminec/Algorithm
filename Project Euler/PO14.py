MAX = 1000001

largestCount=0
largestCountIndex=0
for i in range(13,MAX) :
    count=0
    n=i
    while(n!=1) :
        if(n % 2 == 0) :
            count+=1
            n= int(n/2)
        else :
            count+=1
            n = (n*3) +1
    if (largestCount< count) :
        largestCount = count
        largestCountIndex = i

print(largestCountIndex)
