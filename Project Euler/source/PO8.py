
a = input()


'''
for i in range(0,12) :
    print(a[i])
    
    run 12 times

'''

'find last zeros in first thirteen adjacent digits (and jump?)'
def FindZero(a, b) :
    c = b
    for i in range(b,b+13) :
        'print(i, int(a[i]))'
        if (int(a[i]) == 0) :
            c = i
    if(c==b) :
        return c
    elif(c!=b) :
        return c +1
    

i=FindZero(a,0)

largest = 0

c = i

for i in range(c, len(a)-13) :
    print(i, int(a[i]))   
    if(i >= len(a)-11) :
        break
    if(int(a[i]) == 0) :
       i = i+1
       continue
    elif(int(a[i+12]) == 0) :
       i = i+13
       if( i >= len(a)-12) :
           break
       d = FindZero(a,i)
       continue
    DigitMul = 1
    for j in range(i, i+13) :
       DigitMul = DigitMul * int(a[j])
    if ( largest < DigitMul) :
       largest = DigitMul

    i = i + 1
    
print(largest)


'''print(FindZero(a,0))
print(a[998])
print(len(a))'''
