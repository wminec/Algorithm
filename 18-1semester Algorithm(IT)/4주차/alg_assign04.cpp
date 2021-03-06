#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <search.h>
#include <string.h>

#define N1000 1000
#define N10000 10000
#define N100000 100000

void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int BubbleSort(int A[], int n) {
	int tmp;
	for (int last = n - 1; last >= 1; last--) {
		for (int i = 0; i < last; i++) {
			if (A[i] > A[i + 1]) {
				tmp = A[i];
				A[i] = A[i + 1];
				A[i + 1] = tmp;
			}
		}
	}

	return 0;
}


int SelectionSort(int A[], int n) {
	int max;
	int index;
	int tmp;

	for (int last = n - 1; last >= 1; last--) {
		max = A[last];
		index = last;
		for (int i = last - 1; i >= 0; i--) {
			if (max < A[i]) {
				max = A[i];
				index = i;
			}
		}
		tmp = A[last];
		A[last] = max;
		A[index] = tmp;

	}
	return 0;
}

int InsertionSort(int A[], int n) {
	int tmp, j;
	for (int i = 1; i < n; i++) {
		tmp = A[i];
		j = i - 1;
		while (j >= 0 && A[j] > tmp) {
			A[j + 1] = A[j];
			j = j - 1;
		}
		A[j + 1] = tmp;
	}
	return 0;
}

int Merge(int A[], int p, int q, int r) {
	int i = p, j = q + 1, k = 0;
	int* tmp = (int*)malloc(sizeof(int)*(r - p + 2));

	while (i <= q && j <= r) {
		if (A[i] <= A[j])
			tmp[k++] = A[i++];
		else
			tmp[k++] = A[j++];
	}while (i <= q)
		tmp[k++] = A[i++];
	while (j <= r)
		tmp[k++] = A[j++];
	k = 0;
	for (int i = p; i <= r; i++) {
		A[i] = tmp[k++];
	}
	//    printf("p=%d r=%d\n", p, r);
	//    for (int i = 0; i < k; i++)
	//        printf("%d ", A[i]);
	//    printf("\n");

	return 0;
}

int MergeSort(int A[], int p, int r) {
	int q;
	if (p < r) {
		q = (p + r) / 2;
		MergeSort(A, p, q);
		MergeSort(A, q + 1, r);
		Merge(A, p, q, r);
	}
	return 0;
}

int PartitionPickLast(int A[], int p, int r) {
	int pivot = A[r];
	int i = (p - 1);

	for (int j = p; j <= r - 1; j++) {
		if (A[j] <= pivot) {
			i++;
			swap(&A[i], &A[j]);
		}
	}
	swap(&A[i + 1], &A[r]);

	return (i + 1);
}

int PartitionPickMiddle(int A[], int p, int r) {
	int tmp;
	int pivot = A[p + (r - p) / 2];
	int i = p - 1, j = r + 1;

	while (i <= j) {
		while (A[++i] < pivot);
		while (A[--j] > pivot);
		if (i >= j) break;
		tmp = A[i];
		A[i] = A[j];
		A[j] = tmp;
	}
	return j;
}

int PartitionPickRandom(int A[], int p, int r) {
	int tmp;

	srand(static_cast<unsigned int>(time(NULL)));
	int pivot = (rand() % (r - p)) + p;
	//    printf("\n\n%d\n", pivot);
	tmp = A[pivot];
	A[pivot] = A[r];
	A[r] = tmp;
	return PartitionPickLast(A, p, r);
}

int QuickSortLast(int A[], int p, int r) {
	if (p < r) {
		int q = PartitionPickLast(A, p, r);
		QuickSortLast(A, p, q - 1);
		QuickSortLast(A, q + 1, r);
	}
	return 0;
}

int QuickSortMiddle(int A[], int p, int r) {
	if (p < r) {
		int q = PartitionPickMiddle(A, p, r);
		QuickSortMiddle(A, p, q);
		QuickSortMiddle(A, q + 1, r);
	}
	return 0;
}

int QuickSortRandom(int A[], int p, int r) {
	if (p < r) {
		int q = PartitionPickRandom(A, p, r);
		QuickSortRandom(A, p, q - 1);
		QuickSortRandom(A, q + 1, r);
	}
	return 0;
}

int comparator(const void *p, const void *q)
{
	int l = *(const int *)p;
	int r = *(const int *)q;

	return l - r;
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

int Build_Max_Heap(int A[], int n){
	for (int i = n / 2 -1; i >= 0; i--)
		Max_Heapify(A, n, i);
	return 0;
}

int HeapSort(int A[], int n) {
	Build_Max_Heap(A, n);
	for (int i = n -1; i > 1; i--) {
		swap(&A[0], &A[i]);
		Max_Heapify(A, i - 1, 0);
	}
	return 0;
}

int MakeRivData(int n) {
	FILE *foRiv;

	if (n == N1000)
		foRiv = fopen("Riv1000data.txt", "w");
	else if (n == N10000)
		foRiv = fopen("Riv10000data.txt", "w");
	else
		foRiv = fopen("Riv100000data.txt", "w");

	for (int i = n; i > 0; i--) {
		fprintf(foRiv, "%d ", i);
	}

	fclose(foRiv);

	return 0;
}

int MakeRanData(int n) {
	int RandNum;
	FILE *foRan;

	for (int j = 0; j<10; j++) {
		if (n == N1000) {
			char Path[] = "Ran1000data_0.txt";
			memset(strrchr(Path, '0'), (char)j + 48, 1);
			foRan = fopen(Path, "w");
		}
		else if (n == N10000) {
			char Path[] = "Ran10000data_0.txt";
			memset(strrchr(Path, '0'), (char)j + 48, 1);
			foRan = fopen(Path, "w");
		}
		else {
			char Path[] = "Ran100000data_0.txt";
			memset(strrchr(Path, '0'), (char)j + 48, 1);
			foRan = fopen(Path, "w");
		}

		for (int i = 0; i < n; i++) {
			RandNum = (rand() % (n / 10)) + 1;
			fprintf(foRan, "%d ", RandNum);
		}
		fclose(foRan);
	}

	return 0;
}

int SortingList(int A[], int s, int n) {
	if (s == 0) {
		BubbleSort(A, n);
	}
	else if (s == 1)
		SelectionSort(A, n);
	else if (s == 2)
		InsertionSort(A, n);
	else if (s == 3)
		MergeSort(A, 0, n - 1);
	else if (s == 4) {
		QuickSortLast(A, 0, n - 1);
	}
	else if (s == 5)
		QuickSortMiddle(A, 0, n - 1);
	else if (s == 6)
		QuickSortRandom(A, 0, n - 1);
	else if (s == 7)
		HeapSort(A, n);
	else if (s == 8)
		qsort(A, n, sizeof(int), comparator);

	return 0;
}

int StartCalcSortingTime(float TimeRan[], float TimeRiv[], int* Ran, int* Riv, FILE *fiRiv, int n) {
	float AvgTime;
	FILE *fiRan;
	FILE *testOut;
	time_t startTime, endTime;
	//FILE *a;
	char Path[100];
	float gap;

	//fscanf(fiRan, "%d", &t);
	//printf("\n\n%d\n\n", t);
	for (int i = 0; i < 9; i++) {
		AvgTime = 0;
		for (int j = 0; j < 10; j++) {
			if (n == N1000) {
				strcpy(Path, "Ran1000data_0.txt");
			}
			else if (n == N10000) {
				strcpy(Path, "Ran10000data_0.txt");
			}
			else {
				strcpy(Path, "Ran100000data_0.txt");
			}
			memset(strrchr(Path, '0'), (char)j + 48, 1);
			fiRan = fopen(Path, "r");
			fseek(fiRan, 0, SEEK_SET);

			for (int j = 0; j < n; j++) {
				fscanf(fiRan, "%d ", &Ran[j]);
				//                if(n==N100000)
				//                    printf("%d ",Ran[j]);
			}
			//            printf("\n\n");

			startTime = clock();
			SortingList(Ran, i, n);
			endTime = clock();
			gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);
			AvgTime += gap;
			printf("%d, %d Ran sort end in %f sec\n", i, j, gap);
		}
		TimeRan[i] = AvgTime / 10;
		printf("%d Ran sort end\n", i);

		//printf("\n\nss%d\n\n", Ran[0]);


		fseek(fiRiv, 0, SEEK_SET);
		for (int j = 0; j < n; j++) {
			fscanf(fiRiv, "%d ", &Riv[j]);
		}

		startTime = clock();
		SortingList(Riv, i, n);
		endTime = clock();
		gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);
		TimeRiv[i] = gap;
		//        if (i == 4 && n == N100000) {
		//           testOut = fopen("testQuick1RivData.txt", "w");
		//            for (int j = 0; j<n; j++)
		//                fprintf(testOut, "%d ", Riv[j]);
		//            fclose(testOut);
		//        }
		printf("%d Riv sort end in %f sec\n", i, TimeRiv[i]);
		printf("%d sort end\n\n", i);
	}

	//BubbleSort(t, 10);
	//SelectionSort(t, 10);
	//InsertionSort(t, 10);
	//MergeSort(t, 0, 10-1);
	//QuickSort(t, 0, 10 - 1, 0);
	//QuickSort(t, 0, 10 - 1, 1);
	//QuickSort(t, 0, 10 - 1, 2);
	return 0;
}

int PrintCase(int i) {
	//printf("0 = Bubble, 1 = Selection, 2 = Insertion, 3 = Merge, 4 = Quick1, 5 = Quick2, 6 = Quick3\n\n");
	if (i == 0)
		printf("BubbleSort :	");
	else if (i == 1)
		printf("SelectionSort :	");
	else if (i == 2)
		printf("InsertionSort :	");
	else if (i == 3)
		printf("MergeSort :	");
	else if (i == 4)
		printf("Quick1Sort :	");
	else if (i == 5)
		printf("Quick2Sort :	");
	else if (i == 6)
		printf("Quick3Sort :	");
	else if (i == 7)
		printf("HeapSort :	");
	else if (i == 8)
		printf("qsort :		");

	return 0;
}

int main()
{
	int t[10];
	int *Ran, *Riv;
	float TimeRan1000[9], TimeRan10000[9], TimeRan100000[9];
	float TimeRiv1000[9], TimeRiv10000[9], TimeRiv100000[9];
	int i, random;


	srand(static_cast<unsigned int>(time(NULL)));
	for (i = 0; i < 10; i++) {
		random = (rand() % 10) + 1;
		t[i] = random;
		printf("%d ", t[i]);
	}
	printf("\n");

//	  MakeRanData(N1000);
//	  MakeRanData(N10000);
//	  MakeRanData(N100000);
//	  MakeRivData(N1000);
//	  MakeRivData(N10000);
//	  MakeRivData(N100000);


	FILE *fiRiv;

	//    fiRan10000 = fopen("Ran10000data.txt", "r");
	//    fiRiv10000 = fopen("Riv10000data.txt", "r");
	//    fiRan100000 = fopen("Ran100000data.txt", "r");
	//    fiRiv100000 = fopen("Riv100000data.txt", "r");

	//    for (i = 0; i < N1000; i++) {
	//fscanf(fiRan, "%d ", &Ran[i]);
	//        fscanf(fiRiv, "%d ", &Riv[i]);
	//    }
	//    for (i = 0; i < N10000 - 1; i++) {
	//        fscanf(fiRan10000, "%d ", &Ran10000[i]);
	//        fscanf(fiRiv10000, "%d ", &Riv10000[i]);
	//    }
	//    for (i = 0; i < N100000 - 1; i++) {
	//        fscanf(fiRan100000, "%d ", &Ran100000[i]);
	//        fscanf(fiRiv100000, "%d ", &Riv100000[i]);
	//    }
	//    printf("%d", Riv[500]);
	//for (i = 0; i < 10; i++)
	//        t[i] = 10 - i;
	//BubbleSort(t, 10);
	//SelectionSort(t, 10);
	//InsertionSort(t, 10);
	//MergeSort(t, 0, 10-1);
	//QuickSort(t, 0, 10 - 1, 0);
	//    QuickSortLast(Riv, 0, N1000 - 1);
	//    QuickSortMiddle(t, 0, 10 - 1);
	//QuickSort(t, 0, 10 - 1, 2);
	for (i = 0; i<10; i++)
		printf("%d ", t[i]);
	printf("\n");


	fiRiv = fopen("Riv1000data.txt", "r");
	Ran = (int*)malloc(sizeof(int)*(N1000 + 1));
	Riv = (int*)malloc(sizeof(int)*(N1000 + 1));
	StartCalcSortingTime(TimeRan1000, TimeRiv1000, Ran, Riv, fiRiv, N1000);
	free(Ran);
	free(Riv);
	fclose(fiRiv);



	fiRiv = fopen("Riv10000data.txt", "r");
	Ran = (int*)malloc(sizeof(int)*(N10000 + 1));
	Riv = (int*)malloc(sizeof(int)*(N10000 + 1));
	StartCalcSortingTime(TimeRan10000, TimeRiv10000, Ran, Riv, fiRiv, N10000);
	free(Ran);
	free(Riv);
	fclose(fiRiv);


	fiRiv = fopen("Riv100000data.txt", "r");
	Ran = (int*)malloc(sizeof(int)*(N100000 + 1));
	Riv = (int*)malloc(sizeof(int)*(N100000 + 1));
	StartCalcSortingTime(TimeRan100000, TimeRiv100000, Ran, Riv, fiRiv, N100000);
	free(Ran);
	free(Riv);
	fclose(fiRiv);


	printf("		Ran1000 Riv1000 | Ran10000 Riv10000 | Ran100000 Riv100000\n\n");
	for (i = 0; i < 9; i++) {
		PrintCase(i);
		printf("%.5f  %.5f | %.5f  %.5f | %.5f  %.5f\n", TimeRan1000[i], TimeRiv1000[i], TimeRan10000[i], TimeRiv10000[i], TimeRan100000[i], TimeRiv100000[i]);
	}

	return 0;
}


