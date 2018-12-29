'''
def res1(x) :
    return (x*x*x)+(7*x)+10
def res2(x) :
    return ((x*x*x)+(7*x)+10)%11

print("i", "y*y", "mod11")
for i in range(0,11) :
    print(i,res1(i),res2(i))

'''


A=15
a=11
b=19
n=167

def rev(m) :
    for i in range(0, 200) :
        if (m * i) % n == 1 :
            return i


def resM(px1, py1, px2, py2) :
    if px1 != px2 and py1 != py2 :
        return ((py2-py1) * rev(px2-px1)) % n
    elif px1 == px2 or py1 == py2:
        return (((3*px1*px1) + a)*rev(2*py1)) % n


def resX(px1, px2, m) :
    return ((m*m)-px1-px2) % n

def resY(px1, py1, px3, m) :
    return (m*(px1-px3)-py1) % n

px1=px2=2
py1=py2=7
for i in range(1,A) :
    m=resM(px1, py1, px2, py2)
    px3=resX(px1,px2,m)
    py3=resY(px1,py1,px3,m)
    px1=px3
    py1=py3
    print(px3, py3)

print(px3, py3)
    

