#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<queue>
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

void initNodeArray(Node* NA[]) {
	int i;
	for (i = 0; i < CITYNUM; i++)
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

void BFS_Print_tenHops(Data* data[], Node* node[], int start) {
	queue<QueueData*> q;
	QueueData* qd = newQueueData(start, 0);
	int i = 0;
	q.push(qd);
	check[start] = true;
	while (!q.empty()) {
		QueueData* tmp = q.front();
		q.pop();
		printf("%d - %d Hops : ", i, tmp->hops);
		printf("%s  %f  %f\n", data[tmp->num]->Name, data[tmp->num]->latitude, data[tmp->num]->longitude);
		Node* nTmp = node[tmp->num];
		while (nTmp != NULL) {
			if (tmp->hops + 1 > 10)
				break;
			if (!check[nTmp->num]) {
				check[nTmp->num] = true;
				qd = newQueueData(nTmp->num, tmp->hops + 1);
				q.push(qd);
			}
			nTmp = nTmp->Next;
		}
		free(tmp);
		i++;
	}
}

void DFS(Data* data[], Node* node[], int i, int &c) {
	check[i] = true;
	printf("%d %s  %f  %f\n", c, data[i]->Name, data[i]->latitude, data[i]->longitude);
	c++;
	Node* p = node[i];
	while (p != NULL) {
		i = p->num;
		if (!check[i])
			DFS(data, node, i, c);
		p = p->Next;
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

int find(subset subsets[], int i)
{
	if (subsets[i].parent != i)
		subsets[i].parent = find(subsets, subsets[i].parent);

	return subsets[i].parent;
}

void Union(subset subsets[], int x, int y)
{
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;

	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

int CompEdge(const void* a, const void* b)
{
	const Edge** ia = (const Edge**)a;
	const Edge** ib = (const Edge**)b;
	return ((*ia)->weight > (*ib)->weight) - ((*ia)->weight < (*ib)->weight);
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

void insertRNode(raNode *&root, int r) {
	//NULL인 경우
	root->degree++;
	if (root->rNode == NULL) {
		root->rNode = newRNode(r);
	}
	else {
		rNode* tmp = root->rNode;
		if (tmp->num >= r) {
			root->rNode = newRNode(r);
			root->rNode->Next = tmp;
		}
		else {
			rNode* tNext = tmp->Next;
			while (1) {
				if (tNext == NULL) {
					tmp->Next = newRNode(r);
					break;
				}
				if (tNext->num < r) {
					tmp = tmp->Next;
					tNext = tmp->Next;
				}
				else {
					tmp->Next = newRNode(r);
					tmp->Next->Next = tNext;
					break;
				}
			}
		}
	}
}

void printKrusk(Data* d[], raNode* ra[], int V) {
	int dsum = 0;
	FILE* fo = fopen("mst.txt", "w");
	for (int i = 0; i < V; i++) {
		if (ra[i]) {
			//fprintf(fo, "%s %d %f %f %d ", d[i]->Name,i, d[i]->longitude, d[i]->latitude, ra[i]->degree);
			fprintf(fo, "%d %f %f %d ", i, d[i]->longitude, d[i]->latitude, ra[i]->degree);
			dsum += ra[i]->degree;
			//printf("degree : %d, dsum :  %d\n", ra[i]->degree, dsum);
			rNode* tmp = ra[i]->rNode;
			while (tmp) {
				fprintf(fo, "%d ", tmp->num);
				tmp = tmp->Next;
			}
		}
		fprintf(fo, "\n");
	}
	printf("%d\n", dsum);
	fclose(fo);
}

void KruskalMST(Data* d[], Edge* edge[], int V, int E)
{
	Edge* result[EDGEMAX];  // Tnis will store the resultant MST
	int e = 0;  // An index variable, used for result[]
	int i = 0;  // An index variable, used for sorted edges
	
	qsort(edge, E, sizeof(Edge*), CompEdge);

	//printf("\n%d %d %f\n", edge[E-1]->src, edge[E-1]->dest,edge[E-1]->weight);
	//printf("\n%s\n%s\n", d[edge[E - 1]->src]->Name, d[edge[E - 1]->dest]->Name);
	//for (int a = 0; a < EDGEMAX; a++)
	//	printf("%f\n", edge[a]->weight);
	struct subset *subsets =
		(struct subset*) malloc(V * sizeof(struct subset));

	for (int v = 0; v < V; ++v)
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	while (e < V - 1)
	{
		Edge* next_edge = edge[i++];

		int x = find(subsets, next_edge->src);
		int y = find(subsets, next_edge->dest);


		if (x != y)
		{
			result[e++] = next_edge;
			Union(subsets, x, y);
		}
	}

	printf("Following are the edges in the constructed MST\n");


	raNode* ran[CITYNUM];
	initRANodeArray(ran);
	for (i = 0; i < e; ++i) {
		insertRNode(ran[result[i]->src], result[i]->dest);
		insertRNode(ran[result[i]->dest], result[i]->src);
	}

	printKrusk(d, ran, V);

	for (i = 0; i < e; ++i)
		free(ran[i]);
	return;
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
	Edge* edge[EDGEMAX];
	//fseek(fi2, 0, SEEK_SET);

	//Make Adjacency list
	//and Make graph for Kruskal
	initEdgeArray(edge);
	initNodeArray(nList);
	while (fgets(cLine, MAXLINE, fi2) != NULL) {
		char* end;
		pch = strtok(cLine, "	");
		//printf("%s | ", pch);
		l = dList_Sorted[binarySearch(dList_Sorted, 0, i - 1, pch)]->vNum;
		pch = strtok(NULL, "	");
		pch[strlen(pch) - 1] = 0;
		r = dList_Sorted[binarySearch(dList_Sorted, 0, i - 1, pch)]->vNum;
		w = calDistance(dList[l]->latitude, dList[l]->longitude, dList[r]->latitude, dList[r]->longitude);

		edge[e] = newEdge(l, r, w);
		//printf("%f ", edge[e]->weight);
		//printf("%d : %d %d %f\n", e, edge[e]->src, edge[e]->dest, edge[e]->weight);
		e++;
	}

	printf("e=%d\n", e);
	//printf("%f", edge[0]->weight);
	KruskalMST(dList, edge, i, e);
	//degree의 총 합은 28754이다
	//(14378-1)*2
	printf("End!\n");

	/*
	free(cLine);
	for (int a = 0; a < i; a++)
		free(dList[a]);
	//printf("w");
	for (int a = 0; a < i; a++) {
		if (nList[a])
			free(nList[a]);
	}
	//printf("e");
	for (int a = 0; a < EDGEMAX; a++) {
		if (edge[a])
			free(edge[a]);
	}
	//printf("r");*/
	fclose(fi1);
	//printf("t");
	fclose(fi2);
	//printf("y");
	return 0;
}

