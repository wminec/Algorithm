import math

num=600851475143
FR2=int(math.sqrt(num))
i=0
j=0
DividedNum=0
ModeNum=0
Max=0

Darray= []
Marray= []


for i in range(2, FR2) :
    DividedNum, ModeNum = divmod(num,i)
    if ModeNum==0 :
        Darray.append(i)
        Darray.append(DividedNum)

Darray.sort()
print(Darray)

for i in range(0, len(Darray)) :
    for j in range(2, int(math.sqrt(Darray[i]))) :
        if Darray[i]%j == 0 :
            break

    if j == int(math.sqrt(Darray[i]))-1 :
        Max=Darray[i]
        print(Max)
        print("\n")

print(Max)
