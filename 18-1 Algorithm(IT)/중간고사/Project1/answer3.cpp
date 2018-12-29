#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define ARRMAX 100

bool check_MAX_Heap(int A[], int n, int i){
	int l = i * 2 + 1;
	int r = i * 2 + 2;

	if (l < n){
		if (A[i] < A[l])
			return false;
		else
			return check_MAX_Heap(A, n, l);
	}
		
	if (r < n){
		if (A[i] < A[r])
			return false;
		else
			return check_MAX_Heap(A, n, r);
	}

	return true;
}

int main(){
	int hArr[ARRMAX];
	int i, N;
	bool check;

	while (1){
		scanf("%d", &N);
		if (N == 0)
			break;
		for (i = 0; i < N; i++){
			scanf("%d", &hArr[i]);
			//printf("%d ", hArr[i]);
		}
		check = check_MAX_Heap(hArr, N, 0);
		if (check)
			printf("YES\n");
		else
			printf("NO\n");
			
	}
}