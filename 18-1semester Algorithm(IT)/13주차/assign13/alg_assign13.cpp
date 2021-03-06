#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXSTRING 1000
int c[MAXSTRING][MAXSTRING];
int t[MAXSTRING][MAXSTRING];
char x[MAXSTRING];
char y[MAXSTRING];


//1번 문제
void printLcsRes(int m, int n) {
	if (t[m][n] == 0)
		return;
	else if (t[m][n] == 1) {
		printLcsRes(m - 1, n - 1);
		printf("%c", x[m - 1]);
	}
	else if (t[m][n] == 2)
		printLcsRes(m - 1, n);
	else if (t[m][n] == 3)
		printLcsRes(m, n - 1);
}

// t 1=up and left, 2=up, 3=left
int LCS(int m, int n) {
	for (int i = 0; i <= m; i++)
		c[i][0] = 0;
	for (int j = 0; j <= n; j++)
		c[0][j] = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (x[i - 1] == y[j - 1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				t[i][j] = 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
				t[i][j] = 2;
			}
			else if (c[i - 1][j] < c[i][j - 1]) {
				c[i][j] = c[i][j - 1];
				t[i][j] = 3;
			}
		}
	}

	printLcsRes(m, n);
	printf("\n");
	return c[m][n];
}



#define MAXLEN 50

int max(int a, int b) { return (a > b) ? a : b; }

int P[MAXLEN];
int M[MAXLEN][MAXLEN];

//2번 문제
int CutRod(int n) {
	int* V = (int*)malloc(sizeof(int)*(n + 1));
	V[0] = 0;
	for (int i = 1; i <= n; i++) {
		int max_val = INT_MIN;
		for (int j = 0; j < i; j++)
			max_val = max(max_val, P[j] + V[i - j - 1]);
		V[i] = max_val;
	}

	return V[n];
}



//3번 문제
#define V 100
#define E 300
#define INF 99999

int graph[V][V];
int dist[V][V];
int num[V][V];
int n, m;

void printSolution();

void floydWarshall()
{
	int i, j, k;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			dist[i][j] = graph[i][j];

	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}

	//printSolution();
}

/* A utility function to print solution */
void printSolution()
{
	printf("The following matrix shows the shortest distances"
		" between every pair of vertices \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (dist[i][j] == INF)
				printf("%7s", "INF");
			else
				printf("%7d", dist[i][j]);
		}
		printf("\n");
	}
}

int test(int s, int t) {
	int c = 0;

	for (int i = 0; i < n - 1; i++) {
		if (graph[i][t] != INF && dist[s][i] + graph[i][t] == dist[s][t])
			c++;
	}

	return c;
}


int main()
{
	printf("Problem 1\n");
	scanf("%s", x);
	scanf("%s", y);

	//printf("%d", strlen(x));
	printf("\n");
	printf("%d\n\n",LCS(strlen(x), strlen(y)));

	

	
	printf("Problem 2\n");
	int l;

	scanf("%d", &l);
	for (int i = 0; i < l; i++)
		scanf("%d", &P[i]);
	printf("%d\n\n", CutRod(l));
	//printf("aa");
	

	
	printf("Problem 3\n");
	FILE* fi = fopen("input.txt", "r");

	int s, t;
	int a, b, c;

	fscanf(fi, "%d", &n);
	fscanf(fi, "%d", &m);

	//init graph
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				graph[i][j] = 0;
			else
				graph[i][j] = INF;
		}
	}

	//printf("%d %d\n", n, m);
	for (int i = 0; i < m; i++) {
		fscanf(fi, "%d", &a);
		fscanf(fi, "%d", &b);
		fscanf(fi, "%d", &c);
		//printf("%d %d %d\n", a, b, c);
		graph[a][b] = c;
	}
	fscanf(fi, "%d %d", &s, &t);

	// Print the solution
	floydWarshall();
	//printf("\n");
	printf("%d\n", test(s, t));

	fclose(fi);
	
    return 0;
}

