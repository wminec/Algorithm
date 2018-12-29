#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
/*
#define MAX 100

int findIndex(int data[], int begin, int end);

void func(int data[], int begin, int end) {
	if (begin >= end)
		return; 
	else {
		int index = findIndex(data, begin, end);
		int tmp = data[index];
		data[index] = data[end];
		data[end] = tmp;
		func(data, begin, end - 1);
	}
}

int findIndex(int data[], int begin, int end) {
	if (begin == end)
		return begin;
	int index = findIndex(data, begin + 1, end);
	return (data[begin] > data[index] ? begin : index);
}

int main() {
	int i, data[MAX];
	FILE *fi;

	fi = fopen("data.txt", "r");
	i = 0;
	while (fscanf(fi, "%d", &data[i])!= EOF) {
		i++;
	}
	printf("%d", i);
	func(data, 0, i - 1);

	for (int j = 0; j < i; j++)
		printf("%d ", data[j]);
}
*/

/*
#define MAX 4
int N;
//int maze[MAX][MAX] = { 0,1,1,1,1, 
//					   0,0,1,0,1,
//					   1,0,0,0,1,
//					   1,0,1,0,1,
//					   1,1,1,0,0};
int maze[MAX][MAX] = { 0,0,0,0,
						1,1,1,1,
						1,1,1,1,
						1,1,1,1 };

int MazePath(int x, int y, int dist) {
	if (x < 0 || y < 0 || x >= N || y >= N || maze[x][y] != 0)
		return -1;
	else if (x == N - 1 && y == N - 1) {
		maze[x][y] = 2;
		return dist;
	}
	else {
		maze[x][y] = 2;
		if (MazePath(x - 1, y, dist + 1) >= 0 || MazePath(x, y + 1, dist + 1) >= 0 || MazePath(x + 1, y, dist + 1) >= 0
			|| MazePath(x, y - 1, dist + 1) >= 0) {
			return dist + 1;
		}
		return -1;
	}
}


int main() {
	int res;
	N = 4;

	res = MazePath(0, 0, 0);

	printf("%d\n", res);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ",maze[i][j]);
		}
		printf("\n");
	}
	
}
*/



#define MAX 5
int N;
int K;
int maze[MAX][MAX] = { 0,1,1,1,1,
0,0,1,0,1,
1,0,0,0,1,
1,0,1,0,1,
1,1,1,0,0 };

bool MazePath(int x, int y, int dist) {
	if (x < 0 || y < 0 || x >= N || y >= N || maze[x][y] != 0)
		return false;
	else if (dist > K)
		return false;
	else if (x == N - 1 && y == N - 1) {
		maze[x][y] = 2;
		return true;
	}
	else {
		maze[x][y] = 2;
		if (MazePath(x - 1, y, dist + 1) || MazePath(x, y + 1, dist + 1) || MazePath(x + 1, y, dist + 1)
			|| MazePath(x, y - 1, dist + 1)) {
			return true;
		}
		return false;
	}
}


int main() {
	bool res;
	N = 5;
	K = 8;

	res = MazePath(0, 0, 0);
	for (int a = 0; a < 10; a++) {
		K = a;
		res = MazePath(0, 0, 0);
		printf("%d\n", res);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%d ", maze[i][j]);
			}
			printf("\n");
		}
	}

}


/*

#include <math.h>
#include <time.h>

bool promising(int level);

#define N 14
int cnt=0;
int cols[N + 1];
bool queens_cnt(int level) {
	if (!promising(level))
		return false;
	else if (level == N) {
		cnt++;
		return true;
	}
	for (int i = 1; i <= N; i++) {
		cols[level + 1] = i;
		if (queens_cnt(level + 1)) {
			if (level == N && i == N)
				return true;
			else
				continue;
		}
	}
	//printf("aaa");
	return false;
}

int queens(int level, int n) {
	int sum = 0;
	if (!promising(level))
		return 0;
	else if (level == n)
		return 1;
	for (int i = 1; i <= n; i++) {
		cols[level + 1] = i;
		sum += queens(level + 1, n);
	}
	return sum;
}

bool queens_a(int level) {
	if (!promising(level))
		return false;
	else if (level == N) {
		cnt++;
		return true;
	}
	for (int i = 1; i <= N; i++) {
		cols[level + 1] = i;
		queens_a(level + 1);
	//	if (queens(level + 1)) {
			//return true;
	//	}
	}
	//printf("aaa");
	return false;
}

bool promising(int level) {
	for (int i = 1; i < level; i++) {
		if (cols[i] == cols[level])
			return false;
		else if (level - i == abs(cols[level] - cols[i]))
			return false;
	}
	return true;
}

int main() {
	time_t startTime = 0, endTime = 0;

	for (int i = 1; i < 8; i++) {
		printf("%3d : %d \n", i, queens(0, i));
	}
	return 0;

//	startTime = clock();
//	queens_cnt(0);
//	printf("\n%d", cnt);
//	endTime = clock();
//	printf("runTime is %fsec\n\n", (float)(endTime - startTime) / (CLOCKS_PER_SEC));
	
//	cnt = 0;
//	startTime = endTime = 0;

//	startTime = clock();
//	queens(0);
//	printf("\n%d", cnt);
//	endTime = clock();
//	printf("runTime is %fsec\n\n", (float)(endTime - startTime) / (CLOCKS_PER_SEC));
	
}

*/

/*
#include <iostream>
#include <cmath>

using namespace std;

int board[12];
int n;
int cnt;

void path(int y) {
	int ko = 1;
	if (y == n) {
		for (int i = 0; i < n; i++) {
			printf("(%d, %d)", i, board[i]);
		}
		printf("\n");
		cnt++;
		return;
	}
	for (int i = 0; i<n; i++) {
		ko = 1;
		for (int j = 0; j<y; j++) {
			if (board[j] == i || abs(y - j) == abs(i - board[j])) {
				ko = 0;
				break;
			}
		}
		if (ko) {
			board[y] = i;
			path(y + 1);
		}
	}
}

int main() {
	int k;
	cin >> k;

	while (k--) {
		cin >> n;
		cnt = 0;
		path(0);

		cout << cnt << '\n';
	}

	return 0;
}

//위키백과의 코드이다.
*/