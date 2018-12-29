from math import factorial

a= ( factorial(40) ) / ( factorial(20) * factorial(20) )

print(a)


'''
2x2 에서 오른쪽 아래로만 가서 끝에 도달할 수 있는 모든 경우의 수는
rrdd, rdrd, rddr, drrd, drdr, ddrr 이렇게 6개 이므로

4C2이다. 따라서 20x20에서의 경우의 수는 40C20이므로 위와 같다.
'''

'''
#include <stdio.h>
#define MAX 100

int cache[MAX][MAX] = { 0,0,0, };

int countRoutes(int m, int n) {
	if (n == 0 || m == 0)
		return 1;
	
	if (cache[m][n] != 0)
		return cache[m][n];

	cache[m][n] = countRoutes(m, n - 1) + countRoutes(m - 1, n);
	return cache[m][n];
}

int main() {
	printf("%d", countRoutes(20, 20));
	return 0;
}
향상된 순환탐색 C언어 코드
'''
