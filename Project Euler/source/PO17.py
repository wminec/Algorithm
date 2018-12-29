numChar = {0 : 0, 1 : 3, 2: 3, 3 : 5, 4 : 4,5 : 4,6 : 3, 7 : 5, 8 : 5, 9 : 4,
           10 : 3, 11 : 6, 12 : 6, 13 : 8, 14 : 8, 15 : 7, 16 : 7, 17 : 9, 18 :8, 19 : 8,
           20 : 6, 30 : 6, 40 : 5, 50 : 5, 60 : 5, 70 : 7, 80 : 6, 90 : 6, 100 : 7,
           1000 : 11}

CharSum = 0

for i in range(1, 1001) :
    print(CharSum)
    if(i<21) :
        CharSum += numChar[i]
    elif(i>=21 and i<100) :
        CharSum += numChar[int(i/10)*10] + numChar[i%10]
    elif(i%100==0 and i!=1000) :
        CharSum += numChar[100] + numChar[i/100]
    elif(i>100 and i<1000) :
        CharSum += numChar[int(i/100)] + numChar[100] + 3
        if (i%100 > 10 and i%100 < 20) :
            CharSum += numChar[i%100]
        else :
            CharSum += numChar[int((i%100)/10)*10] + numChar[i%10]
    else :
        CharSum += numChar[1000]

print(CharSum)


'''https://www.mathblog.dk/project-euler-17-letters-in-the-numbers-1-1000/
참고할
'''
