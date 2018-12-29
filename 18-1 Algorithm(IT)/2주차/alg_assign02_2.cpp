#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 100

/*int binarySearch_recursion(int data[], int target, int begin, int end) {
	if (begin > end)
		return end;
	else {
		int middle = (begin + end) / 2;
		if (data[middle] == target)
			return middle;
		else if (data[middle] > target)
			return binarySearch_recursion(data, target, begin, middle - 1);
		else
			return binarySearch_recursion(data, target, middle + 1, end);
	}
}*/

int findFloor_recursion(int data[], int target, int begin, int end) {
	if (begin > end) {
		if (end < 0)
			return -1;
		else {
			return data[end];
		}
	}
	else {
		int middle = (begin + end) / 2;
		if (data[middle] == target) {
			return data[middle];
		}
		else if (data[middle] > target)
			return findFloor_recursion(data, target, begin, middle - 1);
		else
			return findFloor_recursion(data, target, middle + 1, end);
	}
}

int findCeiling_recursion(int data[], int target, int begin, int end, int N) {
	if (begin > end) {
		if (end == (N-1)) {
			return -1;
		}
		else {
			return (data[end + 1]);
		}
		
	}
	else {
		int middle = (begin + end) / 2;
		if (data[middle] == target) {
			return data[middle];
		}
		else if (data[middle] > target)
			return findCeiling_recursion(data, target, begin, middle - 1, N);
		else
			return findCeiling_recursion(data, target, middle + 1, end, N);
	}
}

int main() {
	int data[MAX + 1];
	int N, K;
	int i;
	int floor, ceiling;

	while (1) {
		scanf("%d", &N);
		if (N == 0)
			break;
		for (i = 0; i < N; i++) {
			scanf("%d", &data[i]);
		}
		scanf("%d", &K);
		
		floor = findFloor_recursion(data, K, 0, N - 1);
		ceiling = findCeiling_recursion(data, K, 0, N - 1, N);
		/*if (index < 0) {
			floor = -1;
			ceiling = data[index + 1];
		}
		else if (index == (N-1)) {
			floor = data[index];
			ceiling = -1;
		}
		else {
			floor = data[index];
			ceiling = data[index + 1];
		}*/
		printf("floor = %d\nceiling = %d\n\n", floor, ceiling);
		
	}

	return 0;
}