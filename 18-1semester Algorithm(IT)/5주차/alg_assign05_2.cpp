#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXARR 200000

int swap(int* a, int* b);
int Parent(int i);
int Max_Heap_Insert(int hArr[], int key, int n);
int Max_Heap_Extract(int hArr[], int n);
int Max_Heapify(int A[], int n, int i);
int Build_Max_Heap(int A[], int n);

int swap(int* a, int* b) {
	int	tmp = *a;
	*a = *b;
	*b = tmp;
	return 0;
}

int Parent(int i) {
	if (i % 2 == 0)
		return i / 2;
	else
		return (i - 1) / 2;
}

int Max_Heap_Insert(int hArr[], int key, int n) {
	n++;
	hArr[n - 1] = key;
	int i = n - 1;
	while (i > 0 && hArr[Parent(i)] < hArr[i]) {
		swap(&hArr[i], &hArr[Parent(i)]);
		i = Parent(i);
	}
	return 0;
}

int Max_Heap_Extract(int hArr[], int n) {
	if (n < 1) {
		printf("Heap underflow!!\n");
		return 0;
	}
	int max = hArr[0];
	hArr[0] = hArr[n - 1];
	Max_Heapify(hArr, n - 1, 0);
	return max;
	
}

int Max_Heapify(int A[], int n, int i) {
	int k;
	int l = i * 2 + 1;
	int r = i * 2 + 2;

	if (l > n)
		return 0;
	k = l;
	if (r > n)
		return 0;
	if (A[l] < A[r])
		k = r;
	if (A[i] >= A[k])
		return 0;
	swap(&A[i], &A[k]);
	Max_Heapify(A, n, k);
	return 0;
}

int Build_Max_Heap(int A[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--)
		Max_Heapify(A, n, i);
	return 0;
}

double ArrayRandomInsertDel(int n, int m, int arr[]) {
	double gap;
	int rNum;
	int max;
	int maxIndex;
	int arrLen = n;
	time_t startTime, endTime;

//	printf("arrayRan : ");
	for (int i = 0; i < n; i++) {
		rNum = rand() % n;
		arr[i] = rNum;
	//	printf("%d ", arr[i]);
	}
	//printf("\n");
	startTime = clock();

	for (int i = 0; i < m; i++) {
		rNum = (rand() % 2);
		//0 = del
		//1 = insert
;		if (rNum == 0) {
			max = arr[0];
			maxIndex = 0;
			for (int j = 0; j < arrLen; j++) {
				if (max <= arr[j])
					maxIndex = j;
			}
			swap(&arr[maxIndex], &arr[arrLen - 1]);
			arr[arrLen - 1] = 0;
			arrLen--;
		}
		else {
			arr[arrLen] = rand() % (n+1);
			arrLen++;
		}
	}
	endTime = clock();

	gap = (double)(endTime - startTime) / (CLOCKS_PER_SEC);

	return gap;
}

double hArrayRandomInsertDel(int n, int m, int hArr[]) {
	double gap;
	int rNum;
	int arrLen = n;
	time_t startTime, endTime;

	for (int i = 0; i < n; i++) {
		rNum = rand() % (n + 1);
		hArr[i] = rNum;
	}

	Build_Max_Heap(hArr, arrLen);

	startTime = clock();
	for (int i = 0; i < m; i++) {
		rNum = rand() % 2;
		//0 = del
		//1 = insert

		if (rNum == 0) {
			Max_Heap_Extract(hArr, arrLen);
			arrLen--;
		}
		else {
			Max_Heap_Insert(hArr, rand() % (n + 1), arrLen);
			arrLen++;
		}
	}
	endTime = clock();

	gap = (double)(endTime - startTime) / (CLOCKS_PER_SEC);

	return gap;
}

int main() {
	int n, m;
	int arr[MAXARR], hArr[MAXARR];
	double aTime, hATime;

	srand(static_cast<unsigned int>(time(NULL)));
	scanf("%d %d", &n, &m);

	aTime = ArrayRandomInsertDel(n, m, arr);
	printf("Array end\n");
	hATime = hArrayRandomInsertDel(n, m, hArr);
	printf("heap end\n");

/*
	int t[12] = { 5, 4, 2, 7, 9, 4, 5, 3, 7, 1};

	Build_Max_Heap(t, 10);
	for (int i = 0; i < 10; i++)
		printf("%d ", t[i]);
	printf("\n");
	Max_Heap_Insert(t, 40, 10);
	for (int i = 0; i < 11; i++)
		printf("%d ", t[i]);
	printf("\n");
	Max_Heap_Extract(t, 11);
	for (int i = 0; i < 10; i++)
		printf("%d ", t[i]);

*/

	printf("ArrayTime : %.4f\nHeapArryTime : %.4f\n", aTime, hATime);

	return 0;
}