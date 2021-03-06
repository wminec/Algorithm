#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int makeData();
int LinearFindMin(int* nA, int i, int j);
int AdvancedFindMin(int* nA, int i, int j, int num);
int CompareMinValue(int* nA, struct MinNumGroup* MNG, int i, int j, int GroupingNum);

struct MinNumGroup {
	int value;
	int index;
};

//데이터 갯수를 입력받고, 임의의 데이터를 data.txt로 넣는다.
int makeData()
{
	FILE *fo;
	int num, i, r;

	fo = fopen("data.txt", "w");
	printf("입력한 숫자 만큼 임의의 100 미만의 숫자를 data.txt에 생성합니다. (1 ~ 10000) : ");
	scanf("%d", &num);

	srand(time(NULL));
	fprintf(fo, "%d\n", num);
	for (i = 0; i < num; i++) {
		r = (rand() % 99)+1;
		fprintf(fo, "%d ", r);
	}

	fclose(fo);
	return 0;
}

//선형탐색으로 데이터를 검색하여 최솟값을 찾는다.
int LinearFindMin(int* nA, int i, int j) {
	int min, minIndex, a;

	min = nA[i];
	minIndex = i;
	for (a = i; a <= j; a++) {
		if (min > nA[a]) {
			min = nA[a];
			minIndex = a;
		}
	}

	return minIndex;
}

//N을 루트 N으로 나누면 딱 떨어지거나 소수가 되는데 소수가 될 경우 위로 올린다.
//그러면 그 수가 그룹의 갯수가 된다.
//거기서 i는 루트 N의 배수(0포함)일 때 각 그룹의 최솟값만 보면 된다.
//j는 루트 N의 배수-1 이거나 배열의 가장 마지막 값이 나오면 마지막 까지 최솟값을
//보면 된다.

int AdvancedFindMin(int* nA, int i, int j,int num) {
	int a, b, minIndex;
	int GroupingNum = sqrt(num); //그룹 안에 들어가는 숫자들의 수
	int GroupNum = ceil((float)num / GroupingNum); //그룹의 갯수
//	printf("\n\n%d %d\n\n", GroupingNum, GroupNum);

	struct MinNumGroup* MNG = (struct MinNumGroup*)malloc(sizeof(struct MinNumGroup)* GroupNum);


	//그룹 만드는 for문
	MNG[0].value = nA[0];
	MNG[0].index = 0;
	b = 0;
	for (a = 1; a < num; a++) {
		if (a%GroupingNum == 0 || a == (num - 1)) {
			b++;
			MNG[b].value = nA[a];
			MNG[b].index = a;
		}

		if (MNG[b].value > nA[a]) {
			MNG[b].value = nA[a];
			MNG[b].index = a;
		}
	}

	//확인하는 문장
	/*for(a=0; a<GroupNum; a++)
		printf("\n%d = %d, %d\n", a, MNG[a].value, MNG[a].index);
	*/

	minIndex = CompareMinValue(nA, MNG, i, j, GroupingNum);
	//printf("\n\n advanced data[%d] = %d\n\n", minIndex, nA[minIndex]);
	return minIndex;
}

//최솟값의 index값을 반환한다.
int CompareMinValue(int* nA,struct MinNumGroup* MNG, int i, int j, int GroupingNum) {
	int count = 0; // 반복 횟수를 세는 변수
	int a, b, min, minIndex;

	//printf("%d", MNG[0].value);
	//0이면 그룹에서만
	//1이면 

	//start,end를 결정하자 제일 처음 start를 결정하고, end를 결정한다 
	//i와 j를 GroupingNum으로 나눈 수가 같은 수인지 파악한다.
	//start가 그룹의 처음이 아니면 그 다음 그룹의 첫
	//번째가 될 때까지 최솟값들을 비교한다. 그 다음 그룹의 최솟값을 계산한다
	//

	//i,j가 같은 그룹에 있을 경우
	if (i / GroupingNum == j / GroupingNum) {
		//같은 그룹의 처음과 끝일 경우
		if (i%GroupingNum == 0 && (j + 1) % GroupingNum == 0) {
			//printf("adsfa");
			printf("   %d   ", MNG[i / GroupingNum].value);
			return MNG[i / GroupingNum].index;
		}
		else
		{
		//	printf("qqq");
			min = nA[i];
			minIndex = i;
			for (a = i + 1; a < j + 1; a++) {
				if (min > nA[a]) {
					min = nA[a];
					minIndex = a;
				}
			}
			return minIndex;
		}
	}
	else {//i,j가 다른 그룹에 있을 경우 start와 end를 결정한다
		int ti = i;
		int tj = j;
		int start, end, state;
		/*if (i%GroupingNum == 0) {//i가 그룹의 처음인 경우 start를 그 그룹으로 한다.
			start = i / GroupingNum;
		}
		else {//i가 그룹의 처음이 아닌경우 다음 그룹으로 start를 정한다.
			start = (i / GroupingNum) + 1;
		}
		if ((j + 1) % GroupingNum == 0) {//j가 그룹의 마지막인 경우
			end = j / GroupingNum;
		}
		else {//j가 그룹의 마지막이 아닌 경우
			end = (j / GroupingNum) - 1;
		}*/
		//printf("\n\nstart = %d end = %d\n\n", start, end);
		//start와 end가 같은 경우는 한 그룹밖에 차이가 안나나
		//i가 그룹의 처음이 아니거나, j가 그룹의 마지막이 아닌 경우

		//start와 end의 순서가 역전되는 경우는 한 그룹밖에 차이가 안나나
		//i와 j 둘다 그룹의 처음이 아니거나 그룹의 마지막이 아닌경우

		//i와 j가 1이상 차이가 날 경우는 둘 다 많이 떨어진 경우


		if (i%GroupingNum != 0) {
			min = nA[ti];
			minIndex = ti;
			while (1) {//i가 그룹의 처음이 아닐경우 다음 그룹까지 최솟값을 비교하면서 start를 결정한다.
				ti++;
				count++;
				if (ti%GroupingNum == 0) {
					start = ti / GroupingNum;
					break;
				}
				//printf("a");
				if (min > nA[ti]) {
					min = nA[ti];
					minIndex = ti;
					//printf("\n\n %d = %d \n\n", ti, min);
				}
			}
		}
		else {
			start = i / GroupingNum;
			min = nA[i];
			minIndex = i;
		}
		
		printf("start count = %d\n", count);
		/*while (1) {//j가 그룹의 처음이 아닐경우 다음 그룹까지 최솟값을 비교하면서 end를 결정한다.
			if ((tj + 1) % GroupingNum == 0) {
				end = tj / GroupingNum;
				break;
			}
			//printf("b");
			tj--;
		}*/

		if ((j + 1) % GroupingNum == 0) {//j가 그룹의 마지막인 경우
			end = j / GroupingNum;
		}
		else {//j가 그룹의 마지막이 아닌 경우
			end = (j / GroupingNum) - 1;
		}

		//printf("\ns = %d, e = %d   %d\n", start, end, end - start);
		if ((end - start) >= 0) {//start와 end그룹이 서로 붙어있지 않는경우
			for (a = start; a <= end; a++) {
				//printf("c");
				count++;
				if (min > MNG[a].value) {
					min = MNG[a].value;
					minIndex = MNG[a].index;
				}
			}
		}
		printf("mid count = %d\n", count);

		tj = j;
		while (1) {//j가 그룹의 처음이 아닐경우 다음 그룹까지 최솟값을 비교하면서 end를 결정한다.
			if ((tj + 1) % GroupingNum == 0) {
				end = tj / GroupingNum;
				break;
			}
			count++;
			if (min > nA[tj]) {
				min = nA[tj];
				minIndex = tj;
			}
			tj--;
		}
		printf("end count = %d\n", count);
		return minIndex;
	}

	/*min = nA[i];
	if (ti%GroupingNum != 0) {
		while (1) {
			ti++;
			if (ti%GroupingNum == 0) {
				start = ti / GroupingNum;
				break;
			}
			if()
		}
	}*/

	/*//그룹안에 있는 값들만 확인하면 되는 경우의 수
	if (Ci == 0 && (Cj == 2 || j == num)) {
		min = MNG[i / GroupingNum];
		for (a = i / GroupingNum; a <= j / GroupingNum; a++) {
			if (min > MNG[a]) {
				min = MNG[a];
			}
		}
	}*/

	return 0;
}


int main()
{
	int num, i, j;
	int minIndex;

	//num = makeData();

	FILE *fi;

	fi = fopen("data.txt", "r");
	fscanf(fi, "%d", &num);

	int* nA = (int*)malloc(sizeof(int)*num);
	for (i = 0; i < num; i++) {
		fscanf(fi, "%d", &nA[i]);
	//	printf("%d ", nA[i]);
	}
//	printf("\n");

	fclose(fi);

	/*

	//최악의 값 계산 용이다
	int n = 0;
	int a = sqrt(n); //그룹 안에 들어가는 숫자들의 수
	int b = ceil((float)n / a); //그룹의 갯수

	int max = 0;

	for (i = 1; i <= 10000; i++) {
		a = sqrt(i);
		if (max < a) {
			max = a;
			b = i;
		}
	}

	printf("max(%d) : %d",b, a);

	*/

	while (1) {
		/*printf("처음 index i를 입력하시오 : ");
		scanf("%d", &i);
		if (i == (-1))
			break;
		printf("처음 index j를 입력하시오 : ");
		scanf("%d", &j);
		*/
		scanf("%d", &i);
		if (i == (-1))
			break;
		scanf("%d", &j);
		

		minIndex = LinearFindMin(nA, i, j);

		printf("Lineaer data[%d] = %d\n", minIndex, nA[minIndex]);

		minIndex = AdvancedFindMin(nA, i, j, num);

		printf("Advanced data[%d] = %d\n", minIndex, nA[minIndex]);
	}
	/*int t = sqrt(14);
	int t1 = ceil(14.0 / t);
	printf("\n\n%d %d\n\n", t,t1);*/
	
    return 0;
}



/*
192번째 줄 부터 다시 한번 볼것 

보면 end를 계산하는 것이 두개가 있는데 밑에 있는 것을 위에 있는 것으로

그대로 붙여 넣으면 되나 그러면 리니어와 다른 결과값이 나온다.

그래서 저렇게 해 놓은 것이다.


답

왜 선형탐색을 하면 O(N)이냐면 처음부터 끝까지 다 찾았음에도 데이터를 찾지 못할

경우에 N번 돌기 때문이다.

좀더 발전된 알고리즘에서 최악의 개수는 그룹안의 값이 가장 많아지는 경우로

N이 10000일때 100개씩 그룹핑이 되므로 이 경우가 가장 최악의 경우로 볼 수 있다.

이 때 갯수는 제일 처음 그룹과 제일 마지막 그룹을 제외한 8개의 그룹 

더하기 제일 처음 그룹에서 제일 처음 값을 뺀 가짓수인 99와

마지막 그룹에서 제일 마지막 값을 뺀 가짓수인 99를 더하면

8 + 99 + 99 = 206

이다.

최악은 206이므로 log10(10000)에 2 정도를 곱한 값이다.

그러므로 O(log10(N)) 으로 볼 수 있다.
*/