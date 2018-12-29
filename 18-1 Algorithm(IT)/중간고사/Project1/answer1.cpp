#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define MAX 20

int maze[MAX][MAX];
int N, K;

void initMaze() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			maze[i][j] = 2;
	}
}

int MazePath(int x, int y, int curv, int pastState) {
	int sum = 0;
	if (x < 0 || y < 0 || x >= N || y >= N || maze[x][y] != 0) {
		return 0;
	}
	else if (curv > K) {
		return 0;
	}
	else if (x == N - 1 && y == N - 1) {
		//maze[x][y] = 2;
		return 1;
	}
	else {
		maze[x][y] = 2;
		if (pastState == 4){
			sum += MazePath(x - 1, y, curv, 0);
			sum += MazePath(x, y + 1, curv, 1);
			sum += MazePath(x + 1, y, curv, 2);
			sum += MazePath(x, y - 1, curv, 3);
		}
		else if (pastState % 2 == 0){
			sum += MazePath(x - 1, y, curv, 0);
			sum += MazePath(x, y + 1, curv+1, 1);
			sum += MazePath(x + 1, y, curv, 2);
			sum += MazePath(x, y - 1, curv+1, 3);
		}
		else if (pastState % 2 == 1){
			sum += MazePath(x - 1, y, curv+1, 0);
			sum += MazePath(x, y + 1, curv, 1);
			sum += MazePath(x + 1, y, curv+1, 2);
			sum += MazePath(x, y - 1, curv, 3);
		}

		maze[x][y] = 0;
		return sum;
	}
}

int main()
{
	FILE* fi;
	int T;
	int i, j;
	bool check;

	fi = fopen("input1.txt", "r");
	fscanf(fi, "%d", &T);

	while (T--) {
		fscanf(fi, "%d", &N);
		initMaze();
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				fscanf(fi, "%d", &maze[i][j]);
			}
		}
		fscanf(fi,"%d", &K);
		check = MazePath(0, 0, 0, 4);
		if (check == true)
			printf("YES\n");
		else
			printf("NO\n");
	}
	fclose(fi);
	getchar();
}