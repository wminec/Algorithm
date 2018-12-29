#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#define MAXDATA 300

int Compare(const void * a, const void * b) {
	const char* l = (const char*)a;
	const char* r = (const char*)b;

	return strcmp(l, r);
}

int main() {
	int i, N;
	char* cArray[MAXDATA];

	while (1){
		scanf("%d", &N);
		if (N == 0)
			break;
		for (i = 0; i < N; i++){
			cArray[i] = (char*)malloc(sizeof(char)*MAXDATA);
			scanf("%s", &cArray[i]);
		}
		qsort(cArray, N, sizeof(char*), Compare);
		for (i = 0; i < N; i++){
			printf("%s ",&cArray[i]);
		}
		printf("\n");
		
	}
}