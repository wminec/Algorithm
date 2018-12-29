'이백만'
import sys


print(sys.version)
N = int( input("input a number : ") )
    #init
sieve = {}
for i in range(2, N+1):
    sieve[i] = 0
        
    # Sieve of Eratosthenes
for i in range(2, N+1):
    if sieve[i]==0:
        n=2
        while i*n <= N:
            sieve[i*n]=1
            n+=1

    #print results
result = 0
for i in range(2, N+1):
    if sieve[i]==0:
        result+=i
        'print( i, end="," )'
print("result = ",result)        
input("press any key")
