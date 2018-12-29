print(ord('a'))

f = open("P22_names.txt",'r')
s=f.read()
l=s.split(",")
print(l[0])

f.close()
