#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stack>
#include<float.h>
#include<iostream>
#include <search.h>

#define CITYNUM 20000
#define EDGEMAX 50000
#define CITYNAME 100
#define MAXLINE 500
#define PI acos(-1.0)
//#define PI 3.14159265358979323846

using namespace std;

bool check[CITYNUM];

typedef struct Node;
typedef struct Data;
typedef struct QueueData;

typedef struct Node {
	int num;
	double weight;
	Node* Next;
}Node;

typedef struct Data {
	int vNum;
	char* Name;
	double longitude;
	double latitude;
}Data;

typedef struct QueueData {
	int num;
	int hops;
}QueueData;

typedef struct Edge {
	int src, dest;
	double weight;
}Edge;

typedef struct rNode {
	int num;
	rNode* Next;
}rNode;

typedef struct raNode {
	int degree;
	rNode* rNode;
}raNode;

typedef struct subset {
	int parent;
	int rank;
}subset;

int CompareName(const void * a, const void * b) {
	Data* l = *(Data**)a;
	Data* r = *(Data**)b;
	return strcmp(l->Name, r->Name);
}

Data* newData(char* name) {
	Data* tmp = (Data*)malloc(sizeof(Data));
	tmp->Name = (char*)malloc(CITYNAME);
	strcpy(tmp->Name, name);

	return tmp;
}

Node* newNode(int num, int weight) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->num = num;
	tmp->weight = weight;
	tmp->Next = NULL;
	return tmp;
}

rNode* newRNode(int num) {
	rNode* tmp = (rNode*)malloc(sizeof(rNode));
	tmp->num = num;
	tmp->Next = NULL;
	return tmp;
}

raNode* newRANode() {
	raNode* tmp = (raNode*)malloc(sizeof(raNode));
	tmp->degree = 0;
	tmp->rNode = NULL;
	return tmp;
}

QueueData* newQueueData(int num, int hops) {
	QueueData* tmp = (QueueData*)malloc(sizeof(QueueData));
	tmp->num = num;
	tmp->hops = hops;
	return tmp;
}

Edge* newEdge(int l, int r, double w) {
	Edge* tmp = (Edge*)malloc(sizeof(Edge));
	tmp->src = l;
	tmp->dest = r;
	tmp->weight = w;

	return tmp;
}

void initNodeArray(Node* NA[], int len) {
	int i;
	for (i = 0; i < len; i++)
		NA[i] = NULL;
}

void initEdgeArray(Edge* EA[]) {
	int i;
	for (i = 0; i < EDGEMAX; i++)
		EA[i] = NULL;
}

void initRANodeArray(raNode* ra[]) {
	int i;
	for (i = 0; i < CITYNUM; i++)
		ra[i] = newRANode();
}

void initBoolArray(bool ba[]) {
	for (int i = 0; i < CITYNUM; i++)
		ba[i] = false;
}

double deg2rad(double deg) {
	return (double)(deg * PI / (double)180);
}

double rad2deg(double rad) {
	return (double)(rad * (double)180 / PI);
}
// 매개변수는 첫번째 지점의 위도(lat1), 경도(lon1), 두번째 지점의 위도(lat2), 경도(lon2) 순서이다.
double calDistance(double lat1, double lon1, double lat2, double lon2)
{
	double theta, dist;
	theta = lon1 - lon2;
	dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2))
		+ cos(deg2rad(lat1))
		* cos(deg2rad(lat2)) * cos(deg2rad(theta));
	dist = acos(dist);
	dist = rad2deg(dist);
	dist = dist * 60 * 1.1515;
	dist = dist * 1.609344; // 단위 mile 에서 km 변환.
	dist = dist * 1000.0; // 단위 km 에서 m 로 변환
	return dist;
}

int binarySearch(Data* arr[], int l, int r, char* key) {
	if (r < l)
		return -1;
	else {
		int mid = (l + r) / 2;
		if (strcmp(arr[mid]->Name, key) == 0)
			return mid;
		else if (strcmp(arr[mid]->Name, key) > 0)
			return binarySearch(arr, l, mid - 1, key);
		else
			return binarySearch(arr, mid + 1, r, key);
	}
}

int line_count(FILE *n) {
	char c;
	int lines = 0;

	while ((c = fgetc(n)) != EOF)
	{
		if (c == '\n') ++lines;
	}

	return lines;
}

void insertNode(Node *&root, int r, double w) {
	//NULL인 경우
	if (root == NULL) {
		root = newNode(r, w);
	}
	else {
		Node* tmp = root;
		while (tmp->Next != NULL)
			tmp = tmp->Next;
		tmp->Next = newNode(r, w);
	}
}

/*void printSolution(double* d, int V) {
printf("Vertex   Distance from Source\n");
for (int i = 0; i < V; i++)
printf("%d tt %f\n", i, d[i]);

}*/

/*void printSolution(double* d, int* pi, int s, int t) {
if (t == s) {
printf("%d ", t);
return;
}
printSolution(d, pi, s, pi[t]);
printf("%d ", t);
}*/

void printSolution(Data* data[], double* d, int* pi, int s, int t) {
	if (t == s) {
		printf("%s : %f\n", data[t]->Name, d[t]);
		return;
	}
	printSolution(data, d, pi, s, pi[t]);
	printf("%s : %f\n", data[t]->Name, d[t]);

	return;
}

void Dijkstra(Data* data[], Node* n[], int V, int E, int src, int dst) {
	int i, j, u;
	int sCount = 0;
	double tmp;
	double* d = (double*)malloc(sizeof(double)*V);
	int* pi = (int*)malloc(sizeof(int)*V);
	int* s = (int*)malloc(sizeof(int)*V);
	Node* nTmp;
	//printf("ss");
	for (i = 0; i < V; i++) {
		d[i] = DBL_MAX;
		pi[i] = 0;
		s[i] = 0;
	}
	//printf("qq");
	d[src] = 0;
	while (sCount < V) {
		tmp = DBL_MAX;
		for (j = 0; j < V; j++) {
			if (s[j] == 0 && d[j] < tmp) {
				tmp = d[j];
				u = j;
			}
		}
		//printf("d");
		s[u] = 1;
		sCount++;
		nTmp = n[u];
		int v;
		while (nTmp != NULL) {
			v = nTmp->num;
			if (s[v] == 0 && d[v] > d[u] + nTmp->weight) {
				d[v] = d[u] + nTmp->weight;
				pi[v] = u;
			}
			nTmp = nTmp->Next;
		}
	}
	printf("\n");
	printSolution(data, d, pi, src, dst);
	printf("\nweight : %f", d[dst]);
	printf("\n");
}



int main()
{
	FILE* fi1 = fopen("alabama.txt", "r");
	Data* dList[CITYNUM];
	Data* dList_Sorted[CITYNUM];
	char* cLine = (char*)malloc(MAXLINE);
	char* pch;

	//Data Input
	int i = 0;
	while (fgets(cLine, MAXLINE, fi1) != NULL) {
		char *end;
		//printf("%s\n", cLine);
		pch = strtok(cLine, "	");
		dList[i] = newData(pch);
		dList[i]->vNum = i;
		//printf("aa");
		pch = strtok(NULL, "	");
		dList[i]->longitude = strtod(pch, &end);
		pch = strtok(NULL, "	");
		dList[i]->latitude = strtod(pch, &end);
		dList_Sorted[i] = dList[i];
		i++;
	}
	printf("i=%d\n", i);

	//sorting for binary search
	qsort(dList_Sorted, i, sizeof(Data*), CompareName);

	FILE* fi2 = fopen("roadList2.txt", "r");
	Node* nList[CITYNUM];
	int l, r, e = 0;
	double w = 0;
	//fseek(fi2, 0, SEEK_SET);

	//Make Adjacency list
	//and Make graph for Kruskal
	initNodeArray(nList, CITYNUM);
	while (fgets(cLine, MAXLINE, fi2) != NULL) {
		char* end;
		pch = strtok(cLine, "	");
		//printf("%s | ", pch);
		l = dList_Sorted[binarySearch(dList_Sorted, 0, i - 1, pch)]->vNum;
		pch = strtok(NULL, "	");
		pch[strlen(pch) - 1] = 0;
		r = dList_Sorted[binarySearch(dList_Sorted, 0, i - 1, pch)]->vNum;

		w = calDistance(dList[l]->latitude, dList[l]->longitude, dList[r]->latitude, dList[r]->longitude);


	/*	if (l == 14303 && r == 5553 || l == 5553 && r == 14303)
			printf("%d and %d   w : %f\n", l, r, w);*/


		insertNode(nList[l], r, w);
		insertNode(nList[r], l, w);
		//printf("%f ", edge[e]->weight);
		//printf("%d : %d %d %f\n", e, edge[e]->src, edge[e]->dest, edge[e]->weight);
		e++;
	}

	/*
	gets_s(cLine, MAXLINE);
	int test = dList_Sorted[binarySearch(dList_Sorted, 0, i - 1, cLine)]->vNum;
	printf("num : %d\n", test);

	gets_s(cLine, MAXLINE);
	test = dList_Sorted[binarySearch(dList_Sorted, 0, i - 1, cLine)]->vNum;
	printf("num : %d\n", test);

	//Melvin Creek 14303
	//Lake Espy  5753
	//Kirklands Crossroads 5553
	Node* q = nList[14303];

	while (q) {
		printf("%d %f\n", q->num, q->weight);
		q=q->Next;
	}
	*/

	printf("e=%d\n", e);



	//Marion County - Rankin Fite Airport    11748
	//River Square Plaza Shopping Center     0
	int s, t;
	printf("Enter the Start City Name : ");
	gets_s(cLine, MAXLINE);
	s = dList_Sorted[binarySearch(dList_Sorted, 0, i - 1, cLine)]->vNum;
	printf("Enter the End City Name : ");
	gets_s(cLine, MAXLINE);
	t = dList_Sorted[binarySearch(dList_Sorted, 0, i - 1, cLine)]->vNum;


	/*Node* tNList[6];
	initNodeArray(tNList, 6);
	insertNode(tNList[0], 1, 4);
	insertNode(tNList[1], 0, 4);
	insertNode(tNList[0], 2, 8);
	insertNode(tNList[2], 0, 8);
	insertNode(tNList[1], 2, 11);
	insertNode(tNList[2], 1, 11);
	insertNode(tNList[1], 3, 8);
	insertNode(tNList[3], 1, 8);
	insertNode(tNList[3], 4, 2);
	insertNode(tNList[4], 3, 2);
	insertNode(tNList[2], 4, 7);
	insertNode(tNList[4], 2, 7);
	insertNode(tNList[4], 5, 6);
	insertNode(tNList[5], 4, 6);
	insertNode(tNList[2], 5, 1);
	insertNode(tNList[5], 2, 1);*/

	printf("%s : %d\n%s : %d\n", dList[s]->Name, s, dList[t]->Name, t);
	//V=6, E=8
	//printf("rr");
	Dijkstra(dList, nList, i, e, s, t);

	//printf("%f", edge[0]->weight);
	//degree의 총 합은 28754이다
	//(14378-1)*2
	printf("End!\n");

	
	free(cLine);
	for (int a = 0; a < i; a++)
	free(dList[a]);
	//printf("w");
	for (int a = 0; a < i; a++) {
	if (nList[a])
	free(nList[a]);
	}
	//printf("e");
	/*
	for (int a = 0; a < EDGEMAX; a++) {
	if (edge[a])
	free(edge[a]);
	}*/
	//printf("r");
	fclose(fi1);
	//printf("t");
	fclose(fi2);
	//printf("y");
	return 0;
}

