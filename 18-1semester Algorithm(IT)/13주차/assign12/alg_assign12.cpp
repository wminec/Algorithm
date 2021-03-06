#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define ARRAYMAX 20

int m[ARRAYMAX][ARRAYMAX];
int p[ARRAYMAX];
int t[ARRAYMAX][ARRAYMAX];


void printRes(int l, int r) {
	if (l == r) {
		printf(" A%d ", l);
		return;
	}
	
	printf("(");

	printRes(l, t[l][r]);

	printRes(t[l][r] + 1, r);

	printf(")");
}


int matrixChain(int n) {
	for (int i = 1; i <= n; i++)
		m[i][i] = 0;
	for (int r = 1; r <= n - 1; r++) {
		for (int i = 1; i <= n - r; i++) {
			int j = i + r;
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
			t[i][j] = i;
			for (int k = i + 1; k <= j - 1; k++) {
				if (m[i][j] > m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]) {
					m[i][j] = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
					t[i][j] = k;
				}
			}
		}
	}

	printf("%d\n", m[1][n]);
	printRes(1, n);


	return m[1][n];
}


int main()
{
	FILE* fi = fopen("input.txt", "r");
	int n;

	fscanf(fi, "%d", &n);
	for (int i = 0; i <= n; i++) {
		fscanf(fi, "%d ", &p[i]);
	}

	//printf("\n%d", matrixChain(n));
	matrixChain(n);
    return 0;
}

