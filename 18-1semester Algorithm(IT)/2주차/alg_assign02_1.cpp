#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 100

int twoSum(int data[], int N, int K);
int twoSum_recursion(int data[], int begin, int end, int K);

int twoSum(int data[], int N, int K) {
	int start = 0, end = N - 1;
	int count = 0;
	while (start < end) {
		int sum = data[start] + data[end];
		if (sum > K)
			end--;
		else if (sum < K)
			start++;
		else {
			count++;
			start++;
			end--;
		}
	}

	printf("twoSum count = %d\n", count);
	return 0;
}

int twoSum_recursion(int data[], int begin, int end, int K) {
	//printf("a");
	if (begin >= end)
		return 0;
	else {
		int sum = data[begin] + data[end];
		if (sum == K) {
			return 1 + twoSum_recursion(data, begin + 1, end - 1, K);
		}
		else if (data[begin] + data[end] < K) {
			return twoSum_recursion(data, begin + 1, end, K);
		}
		else {
			return twoSum_recursion(data, begin, end - 1, K);
		}
	}
}

int main()
{
	int data[MAX + 1];
	int N, K;
	int i;

	while (1) {
		scanf("%d", &N);
		if (N == 0)
			break;
		for (i = 0; i < N; i++) {
			scanf("%d", &data[i]);
		}
		scanf("%d", &K);
		twoSum(data, N, K);
		printf("twoSum_recursion count = %d\n\n", twoSum_recursion(data, 0, N - 1, K));
	}

    return 0;
}

