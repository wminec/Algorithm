#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX 16

int maze[MAX + 1][MAX + 1];

void initMaze() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			maze[i][j] = 1;
	}
}

int calcDist(int x, int y, int xy, int pm, int N) {
	//xy 1=x, 2=y
	//pm 1=p, 2=m
	//printf("x=%d y=%d\n\n", x, y);
	int i;
	if (xy == 1) {
		if (pm == 1) {
			for (i = 1; i < N; i++) {
				if (maze[x + i][y] == 1)
					return i - 1;
				else if (x + i == N - 1)
					return i;
			}
		}
		else {
			for (i = 1; i < N; i++) {
				if (maze[x - i][y] == 1)
					return i - 1;
				else if (x - i == 0)
					return i;
				
			}
		}
	}
	else {
		if (pm == 1) {
			for (i = 1; i < N; i++) {
				if (maze[x][y + i] == 1)
					return i - 1;
				else if (y + i == N-1) {
					return i;
				}
			
			}
		}
		else {
			for (i = 1; i < N; i++) {
				if (maze[x][y - i] == 1)
					return i - 1;
				else if (y - i == 0)
					return i;
				
			}
		}
	}
	return 0;
}

bool MazePath(int x, int y, int N) {

	//if (x < 0 || y < 0 || x >= N || y >= N || maze[x][y] != 0)
	if (maze[x][y] != 0)
		return false;
	else if (x == N - 1 && y == N - 1) {
		maze[x][y] = 2;
		return true;
	}
	else {
		maze[x][y] = 2;
		if (MazePath(x - calcDist(x,y,1,2, N), y, N) || MazePath(x, y + calcDist(x, y, 2, 1, N), N) || MazePath(x + calcDist(x, y, 1, 1, N), y, N)
			|| MazePath(x, y - calcDist(x, y, 2, 2, N), N)) {
			return true;
		}
		return false;
	}
}

int main() {
	FILE *fi;
	int T, N;
	int i, j;
	fi = fopen("input2.txt", "r");
	fscanf(fi, "%d", &T);

	while (T--) {
		initMaze();
		fscanf(fi, "%d", &N);

		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				fscanf(fi, "%d", &maze[i][j]);
			}
		}
		if (MazePath(0, 0, N))
			printf("YES\n");
		else
			printf("NO\n");
	}

	fclose(fi);
	return 0;

}