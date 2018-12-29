Month = {1:31, 2:28, 3 : 31, 4:30, 5:31, 6:30, 7:31, 8:31, 9:30, 10:31, 11:30, 12:31,
         13 : 29}

Year = 1900
SundayCount = 0
dayCount = 1
index = 1
while 1 :
    if dayCount== 0 :
        SundayCount += 1
        print(Year, index)
    if index != 2 :
        dayCount += Month[index]
    else :
        if Year % 4 == 0 :
            if Year % 100 == 0 and Year % 400 != 0:
                dayCount+=Month[index]
            else :
                dayCount+=Month[13]
    index+=1
    '''print("dayCount : ", dayCount)'''
    dayCount = dayCount%7
    if index==13 :
        index=1
        Year+=1

    if Year == 2001 :
        break

print(SundayCount)
