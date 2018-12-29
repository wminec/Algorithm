#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#define MAXCOM 30
#define MAXDATA 300
#define MAXDATANUM 1000

struct data {
	char Name[MAXDATA];
	char Company[MAXDATA];
	char Address[MAXDATA];
	char Zipcode[MAXDATA];
	char Phones[MAXDATA];
	char Email[MAXDATA];
};

int CompareName(const void * a, const void * b) {
	struct data *l = *(struct data**)a;
	struct data *r = *(struct data**)b;

	return strcmp(l->Name, r->Name);
}

int CompareCompany(const void * a, const void * b) {
	struct data *l = *(struct data**)a;
	struct data *r = *(struct data**)b;

	return strcmp(l->Company, r->Company);
}

int CompareAddress(const void * a, const void * b) {
	struct data *l = *(struct data**)a;
	struct data *r = *(struct data**)b;

	return strcmp(l->Address, r->Address);
}

int CompareZipcode(const void * a, const void * b) {
	struct data *l = *(struct data**)a;
	struct data *r = *(struct data**)b;

	return strcmp(l->Zipcode, r->Zipcode);
}

int ComparePhones(const void * a, const void * b) {
	struct data *l = *(struct data**)a;
	struct data *r = *(struct data**)b;

	return strcmp(l->Phones, r->Phones);
}

int CompareEmail(const void * a, const void * b) {
	struct data *l = *(struct data**)a;
	struct data *r = *(struct data**)b;

	return strcmp(l->Email, r->Email);
}

int rtrim(char* str) {
	long pos = strlen(str) - 1;
	//printf("\ntrim pos : %d\n", pos);

	for (; pos >= 0; pos--) {
		if (str[pos] == ' ')
			str[pos] = NULL;
		else
			return 0;
	}
	return 0;
}

int ltrim(char* str) {
	int i = 0;
	int len = strlen(str);
//	printf("\nstrltrim : %d\n", len);
	if (str[0] != ' ')
		return 0;
	while(1){
		if (str[i] != ' ') {
			for (int j = 0; j < len - i; j++)
				str[j] = str[i + j];
			str[len - 1] = NULL;
			break;
		}else
			i++;
	}
	return 0;
}

int trim(char* str) {
	rtrim(str);
	ltrim(str);
	
	return 0;
}

int InputDataToCArray(FILE* fi, char* cData, int i) {
	int j = 0;
	char c;

	memset(cData, 0, MAXDATA);
	while (1) {
		fscanf(fi, "%c", &c);
		//printf("c = %c", c);
		if (c == '|' || c == 10) {
			//printf("\n\ncdata : %s'\n\n", cData);
			trim(cData);
			//printf("a\n\ntc cdat : %s'\n\n", cData);
			return 0;
		}
		cData[j++] = c;
	}
	return 0;
}

int InputData(FILE* fi, struct data* data) {
	int i, j = 0;

	for(i=0; i<6; i++) {
		if (i == 0)
			InputDataToCArray(fi, data->Name, i);
		else if (i == 1) {
			InputDataToCArray(fi, data->Company, i);
		//	printf("\n\n%s\n\n", data->Company);
		}
		else if (i == 2)
			InputDataToCArray(fi, data->Address, i);
		else if (i == 3)
			InputDataToCArray(fi, data->Zipcode, i);
		else if (i == 4)
			InputDataToCArray(fi, data->Phones, i);
		else
			InputDataToCArray(fi, data->Email, i);
		//printf("i = %d\n", i);
		
	}
	return 0;
}


int main() {
	FILE *fi;
	struct data* dataArr[MAXDATANUM];
	int i, s = 0;
	char command[MAXCOM];
	char* cmd;
	char c;

	//printf("%d %c\n\n", '|', '|');
	while (1) {
		fgets(command, MAXCOM, stdin);
		//printf("%c %c %c\n", command[strlen(command) - 2], command[strlen(command) - 1], command[strlen(command)]);
		command[strlen(command) - 1] = NULL;
		if (command[0] == 'r') {
			i = 0;
			//printf("%s\n", command);
			cmd = strrchr(command, ' ') + 1;
			//printf("%s___", cmd);
			fi = fopen(cmd, "r");

			int a = 0;
			while (1) {
				fscanf(fi, "%c", &c);
				if (c == 10) {
					if (a != 0)
						break;
					s++;
					a++;
				}
				else
					a = 0;

			}
			//한명의 데이터가 끝나면 ASCII CODE 10이 나온다. 10 = LINE FEED
			//한명의 데이터는 |, 즉 ASCII CODE 124로 구분된다.
			fseek(fi, 0, SEEK_SET);
			for(int i=0; i<s; i++){
				struct data* tmp = (struct data*)malloc(sizeof(struct data));
				InputData(fi, tmp);
				dataArr[i] = tmp;
				//printf("%s\n%s\n%s\n%s\n%s\n%s\n\n", dataArr[i]->Name, dataArr[i]->Company, dataArr[i]->Address, dataArr[i]->Zipcode, dataArr[i]->Phones, dataArr[i]->Email);
			}
			//500개의 데이터다
		}
		else if (command[0] == 's') {
			char* a = strrchr(command, ' ') + 1;
			if (*a == 'n')
				qsort(dataArr, s, sizeof(struct data*), CompareName);
			else if (*a == 'c')
				qsort(dataArr, s, sizeof(struct data *), CompareCompany);
			else if (*a == 'a')
				qsort(dataArr, s, sizeof(struct data *), CompareAddress);
			else if (*a == 'z')
				qsort(dataArr, s, sizeof(struct data *), CompareZipcode);
			else if (*a == 'p')
				qsort(dataArr, s, sizeof(struct data *), ComparePhones);
			else if (*a == 'e')
				qsort(dataArr, s, sizeof(struct data *), CompareEmail);

		}
		else if (command[0] == 'p') {
			for (i = 0; i < s; i++) {
				printf("%d", i);
				printf("%s\n", dataArr[i]->Name);
				printf("	Company: %s\n", dataArr[i]->Company);
				printf("	Address: %s\n", dataArr[i]->Address);
				printf("	Zipcode: %s\n", dataArr[i]->Zipcode);
				printf("	Phones: %s\n", dataArr[i]->Phones);
				printf("	Email: %s\n", dataArr[i]->Email);
			}
		}
		else if(command[0] = 'e')
			break;
		//printf("%s\n%s\n%s\n%s\n%s\n%s", dataArr[0]->Name, dataArr[0]->Company, dataArr[0]->Address, dataArr[0]->Zipcode, dataArr[0]->Phones, dataArr[0]->Email);
	}

}