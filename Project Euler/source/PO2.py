num1=1
num2=2
temp=0
sum=0

while (num1 < 4000000 and num2 < 40000000) :
    if num2 % 2 == 0 :
        sum += num2
    temp=num1
    num1=num2
    num2+=temp

print(sum)
