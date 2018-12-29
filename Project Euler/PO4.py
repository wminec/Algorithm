num=998001
NumArray = []
DNumArray = []
check=0

while len(NumArray) < 10 :
    NStr=str(num)
    for i in range(0, 3) :
        if NStr[i] != NStr[5-i] :
            break
        if i==2 :
            if num%11 == 0 :
                DNum=999
                while DNum!=500 :
                    a, b = divmod(num, DNum)
                    if  len(str(a))<4 and b == 0 :
                        NumArray.append(num)
                        DNumArray.append(a)
                        print(a)
                        
                    DNum-=1
    num-=1
    if num < 100001 :
        break
    

print(NumArray)
print(DNumArray)
