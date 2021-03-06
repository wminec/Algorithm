#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX 16

int N, K;
int maze[MAX][MAX];

void initMaze() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			maze[i][j] = 2;
	}
}

/*
int MazePath(int x, int y, int dist) {
	int sum = 0;
	if (x < 0 || y < 0 || x >= N || y >= N || maze[x][y] != 0) {
		return 0;
	}
	else if (dist > K) {
		return 0;
	}
	else if (x == N - 1 && y == N - 1) {
		//maze[x][y] = 2;
		return 1;
	}
	else {
		maze[x][y] = 2;
		sum += MazePath(x - 1, y, dist + 1);
		sum += MazePath(x, y + 1, dist + 1);
		sum += MazePath(x + 1, y, dist + 1);
		sum += MazePath(x, y - 1, dist + 1);

		maze[x][y] = 0;
		return sum;
	}
}
*/

int MazePath(int x, int y, int dist, int boom) {
	int sum = 0;
	if (x < 0 || y < 0 || x >= N || y >= N || maze[x][y] == 2) {
		return 0;
	}
	if (maze[x][y] == 1) {
		if (boom == 0)
			return 0;
		else {
			maze[x][y] = 0;
			sum+=MazePath(x, y, dist, boom - 1);
			maze[x][y] = 1;
			return sum;
		}
	}
	else if (dist > K) {
		return 0;
	}
	else if (x == N - 1 && y == N - 1) {
		//maze[x][y] = 2;
		return 1;
	}
	else {
		maze[x][y] = 2;
		sum += MazePath(x - 1, y, dist + 1, boom);
		sum += MazePath(x, y + 1, dist + 1, boom);
		sum += MazePath(x + 1, y, dist + 1, boom);
		sum += MazePath(x, y - 1, dist + 1, boom);

		maze[x][y] = 0;
		return sum;
	}
}

/*int MazePath(int maze[][MAX+1],int x, int y, int dist, int K,int N) {
	int sum = 0;
	int Tmaze[MAX+1][MAX+1];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			Tmaze[i][j] = maze[i][j];
	}

	if (x < 0 || y < 0 || x >= N || y >= N || maze[x][y] != 0)
		return false;
	else if (dist > K)
		return false;
	else if (x == N - 1 && y == N - 1) {
		//Tmaze[x][y] = 2;
		return 1;
	}
	else {
		Tmaze[x][y] = 2;
		sum += MazePath(Tmaze, x - 1, y, dist + 1, K, N);
		sum += MazePath(Tmaze, x, y + 1, dist + 1, K, N);
		sum += MazePath(Tmaze, x + 1, y, dist + 1, K, N);
		sum += MazePath(Tmaze, x, y - 1, dist + 1, K, N);
	}
	return sum;
}
*/


int main()
{
	FILE *fi;
	int T;
	int i, j;
	int sum;

	fi = fopen("input3.txt", "r");
	fscanf(fi,"%d", &T);

	while (T--) {
		fscanf(fi,"%d", &N);
		initMaze();

		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				fscanf(fi,"%d", &maze[i][j]);
			}
		}
		
		fscanf(fi,"%d", &K);

		sum = MazePath(0, 0, 0, 1);
		printf("sum = %d\n", sum);
	}
    return 0;
	fclose(fi);
}

