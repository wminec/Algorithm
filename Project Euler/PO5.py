temp=0
RNA = []
NA = []

for i in range(0,20) :
    RNA.append(0)
    NA.append(0)


for i in range(2, 21) :
    DA = []
    temp=i
    j=1
    while 1 :
        j+=1
        print(temp)
        if temp%j==0 :
            temp, mod = divmod(temp, j)
            if mod == 0 :
                DA.append(j)
                j=1
            if temp == 1:
                break
    print("sefsfe",i)
    print(DA)
    for k in range(0,20) :
        NA[k] = 0
    for k in range(0, len(DA)) :
        NA[DA[k]-1]+=1
    for k in range(0,20) :
        if NA[k]> RNA[k] :
            RNA[k]=NA[k]
    print(NA)
    print(RNA)

mul=1

for i in range(0, 20) :
    for j in range(0, RNA[i]) :
        mul*=(i+1)

print(mul)
