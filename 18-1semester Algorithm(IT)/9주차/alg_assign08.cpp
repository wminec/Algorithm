#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MULTIPLIER 31
#define NHASH 4093 // NHASH는 해쉬 테이블의 크기
#define cSize 30

typedef struct suffix Suffix;
typedef struct node Node;
typedef struct prefix Prefix;

typedef struct suffix {
	char *sword; // suffix인 단어
	int freq; // 등장횟수
	Suffix* next; // 다음 노드의 주소
}Suffix;

typedef struct prefix {
	char *pword1; // prefix를 구성하는 첫 단어
	char *pword2; // prefix를 구성하는 두 번째 단어
	Suffix *suf; // suffix들의 연결리스트의 첫 번째 노드의 주소
	int sumFreq; // suffix들의 등장횟수(freq)의 합
} Prefix;

typedef struct node {
	Prefix *data;
	Node *next;
}Node;

unsigned int hash(char *key1, char *key2) {
	unsigned int h = 0;
	unsigned char *p;
	for (p = (unsigned char *)key1; *p != '\0'; p++)
		h = MULTIPLIER * h + *p;
	for (p = (unsigned char *)key2; *p != '\0'; p++)
		h = MULTIPLIER * h + *p;
	return h % NHASH;
}

Node* newNode() {
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->next = NULL;
	return tmp;
}

Prefix* newPrefix(char* key1, char* key2) {
	Prefix* tmp = (Prefix*)malloc(sizeof(Prefix));
	tmp->pword1 = (char*)malloc(cSize);
	tmp->pword2 = (char*)malloc(cSize);
	strcpy(tmp->pword1, key1);
	strcpy(tmp->pword2, key2);
	tmp->sumFreq = 1;
	return tmp;
}

Suffix* newSuffix(char* key) {
	Suffix* tmp = (Suffix*)malloc(sizeof(Suffix));
	tmp->sword = (char*)malloc(cSize);
	strcpy(tmp->sword, key);
	tmp->freq = 1;
	tmp->next = NULL;
	return tmp;
}

void initHTable(Node* HT[]) {
	int i;
	for (i = 0;  i < NHASH; i++)
		HT[i] = NULL;
}

Prefix* findPrefix(Node* node, char* key1, char* key2) {
	while (1) {
		//Prefix값 찾기 시작
		if (strcmp(node->data->pword1, key1) == 0 && strcmp(node->data->pword2, key2) == 0) {
			//Prefix에서 값을 찾았을 경우
			return node->data;
		}
		//Prefix값을 찾지 못하였을 경우
		if (node->next == NULL) {
			return NULL;
		}
		node = node->next;
	}
}

Suffix* findSuffix(Prefix* prefix, char* key3) {
	Suffix* suf = prefix->suf;
	while (1) {
		if (strcmp(suf->sword, key3) == 0)
			return suf;
		if (suf->next == NULL)
			return NULL;
		suf = suf->next;
	}
}

void insertData(Node *&root, char* key1, char* key2, char* key3) {
	//htable의 값이 NULL인 아닌 경우
	if (root == NULL) {
		root = newNode();
		//printf("1");
		root->next = NULL;
		root->data = newPrefix(key1, key2);
		root->data->suf = newSuffix(key3);
	}
	//htable의 값이 NULL이 아닌 경우
	else {
		Node* node = root;
		while (1) {
			//Prefix값 찾기 시작
			if (strcmp(node->data->pword1, key1) == 0 && strcmp(node->data->pword2, key2) == 0) {
				//Prefix에서 값을 찾았을 경우
				//Suffix에 값이 있는가 확인한다.
				Suffix* suf = node->data->suf;
				while (1) {
					if (strcmp(suf->sword, key3) == 0) {
						suf->freq += 1;
						node->data->sumFreq += 1;
						break;
					}
					if (suf->next == NULL) {
						Suffix* tmp = newSuffix(key3);
						suf->next = tmp;
						node->data->sumFreq += 1;
						break;
					}
					suf = suf->next;
				}
				break;
			}
			//Prefix값을 찾지 못하였을 경우
			if (node->next == NULL) {
				node->next = newNode();
				node->next->data = newPrefix(key1, key2);
				node->next->data->suf = newSuffix(key3);
				break;
			}
			node = node->next;
		}
	}
}


int main()
{
	Node *htable[NHASH];
	FILE* fi;
	int hIndex;
	int i = 0;

	fi = fopen("HarryPotter.txt", "r");
	initHTable(htable);
	char *key1, *key2, *key3;
	key1 = (char*)malloc(cSize);
	key2 = (char*)malloc(cSize);
	key3 = (char*)malloc(cSize);
	fscanf(fi, "%s", key1);
	fscanf(fi, "%s", key2);

	while (1) {
		fscanf(fi, "%s", key3);
		hIndex = hash(key1, key2);
		insertData(htable[hIndex], key1, key2, key3);
		if (strcmp(key3, "[end]") == 0) {
			break;
		}

		strcpy(key1, key2);
		strcpy(key2, key3);
		i++;
	}

	int r;
	i = 0;
	while (htable[i++] == NULL && i < NHASH);
	i -= 1;
	Prefix* pref = htable[i]->data;
	strcpy(key1, pref->pword1);
	strcpy(key2, pref->pword2);
	srand((int)time(0));
	for (i = 0; i < 1000; i++) {
		if (i != 0) {
			pref = findPrefix(htable[hash(key1, key2)], key1, key2);
		}
		r = (rand() % pref->sumFreq) + 1;
		Suffix* suff = pref->suf;
		while (1) {
			r -= suff->freq;
			if (r <= 0) {
				strcpy(key3, suff->sword);
				break;
			}
			suff = suff->next;
		}
		if (strcmp(key3, "[end]") == 0)
			break;
		printf("%s ", key3);
		strcpy(key1, key2);
		strcpy(key2, key3);
	}
	return 0;
}

