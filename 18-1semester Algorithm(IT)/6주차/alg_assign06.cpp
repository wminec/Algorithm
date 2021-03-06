#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#define MAXCOM 30
#define MAXDATA 300
#define MAXDATANUM 1000


void printNode(struct data* root);
struct data * minValueNode(struct data* node);

struct data {
	char Name[MAXDATA];
	char Company[MAXDATA];
	char Address[MAXDATA];
	char Zipcode[MAXDATA];
	char Phones[MAXDATA];
	char Email[MAXDATA];
	struct data *left, *right, *parent;
};

struct data* makeEmptyNode() {
	struct data* tmp = (struct data*)malloc(sizeof(struct data));
	tmp->left = tmp->right = tmp->parent = NULL;
	return tmp;
}

struct data* insert(struct data* node, struct data* data)
{
	/* 1. If the tree is empty, return a new,
	single node */
	if (node == NULL)
		return data;
	else
	{
		struct data *temp;

		/* 2. Otherwise, recur down the tree */
		if (strcmp(node->Name, data->Name) >= 0)
		{
			temp = insert(node->left, data);
			node->left = temp;
			temp->parent = node;
		}
		else
		{
			temp = insert(node->right, data);
			node->right = temp;
			temp->parent = node;
		}

		/* return the (unchanged) node pointer */
		return node;
	}
}

//int CompareName(const void * a, const void * b) {
//	struct data *l = *(struct data**)a;
//	struct data *r = *(struct data**)b;

//	return strcmp(l->Name, r->Name);
//}

struct data* search(struct data* root, char* key)
{
	// Base Cases: root is null or key is present at root
	if (root == NULL || strcmp(root->Name,key) == 0)
		return root;

	// Key is greater than root's key
	if (strcmp(root->Name, key) < 0)
		return search(root->right, key);

	// Key is smaller than root's key
	return search(root->left, key);
}

struct data* trace(struct data* root, char* key)
{
	printf("%s\n", root->Name);
	// Base Cases: root is null or key is present at root
	if (root == NULL || strcmp(root->Name, key) == 0)
		return root;

	// Key is greater than root's key
	if (strcmp(root->Name, key) < 0)
		return trace(root->right, key);

	// Key is smaller than root's key
	return trace(root->left, key);
}

struct data* Ceil(struct data *root, char* key)
{
	struct data* ceil = NULL;

	while (root != NULL) {
		//printf("%s\n", root->Name);
		if (strcmp(root->Name, key) > 0) {
			ceil = root;
			root = root->left;
		}
		else if (strcmp(root->Name, key) < 0) {
			root = root->right;
		}
		else {
			return root;
		}
	}
	//printf("end loop name = %s\n", root->Name);
	/*if (root != NULL) {
		if (root->right)
			ceil = minValueNode(root->right);
	}*/

	if (ceil != NULL)
		return ceil;
	else
		return NULL;
}

struct data* Floor(struct data *root, char* key)
{
	struct data* floor = NULL;

	while (root != NULL) {
		//printf("%s\n", root->Name);
		if (strcmp(root->Name, key) < 0) {
			floor = root;
			root = root->right;
		}
		else if (strcmp(root->Name, key) > 0) {
			root = root->left;
		}
		else {
			return root;
		}
	}
	//printf("end loop name = %s\n", root->Name);
	/*if (root != NULL) {
	if (root->right)
	ceil = maxValueNode(root->left);
	}*/

	if (floor != NULL)
		return floor;
	else
		return NULL;
}

/*
char* Ceil(struct data *root, char* key)
{
	//printf("C = %s\n", root->Name);
	// Base case
	if (root == NULL) {
		char* c = (char*)malloc(sizeof(char));
		*c = NULL;
		return c;
	}

	// We found equal key
	if (strcmp(root->Name, key) == 0)
		return root->Name;

	// If root's key is smaller, ceil must be in right subtree
	if (strcmp(root->Name, key) < 0)
		return Ceil(root->right, key);

	// Else, either left subtree or root has the ceil value
	char* ceil = Ceil(root->left, key);
	//printf("%d\n",strcmp(ceil,key));
	return (strcmp(ceil, key) >= 0) ? ceil : root->Name;
}
*/

/*char* Floor(struct data *root, char* key)
{
	printf("F = %s\n", root->Name);
	// Base case
	if (root == NULL) {
		char* c = (char*)malloc(sizeof(char));
		*c = NULL;
		return c;
	}

	// We found equal key
	if (strcmp(root->Name, key) == 0)
		return root->Name;

	// If root's key is bigger, floor must be in left subtree
	if (strcmp(root->Name, key) > 0)
		return Floor(root->left, key);

	// Else, either right subtree or root has the floor value
	char* floor = Floor(root->right, key);
	printf("%d\n",strcmp(floor,key));
	return (strcmp(floor, key) <= 0) ? floor : root->Name;
}*/


struct data * minValueNode(struct data* node)
{
	struct data* current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}

struct data* inOrderSuccessor(struct data *root, struct data *n)
{
	// step 1 of the above algorithm 
	if (n->right != NULL)
		return minValueNode(n->right);

	// step 2 of the above algorithm
	struct data* p = n->parent;
	while (p != NULL && n == p->right)
	{
		n = p;
		p = p->parent;
	}
	return p;
}

/* Given a binary search tree and a key, this function deletes the key
and returns the new root */
/*struct data* deleteNode(struct data* root, char* key)
{
	// base case
	if (root == NULL) return root;

	// If the key to be deleted is smaller than the root's key,
	// then it lies in left subtree
	if (strcmp(root->Name, key)>0)
		root->left = deleteNode(root->left, key);

	// If the key to be deleted is greater than the root's key,
	// then it lies in right subtree
	else if (strcmp(root->Name,key)<0)
		root->right = deleteNode(root->right, key);

	// if key is same as root's key, then This is the node
	// to be deleted
	else
	{
		// node with only one child or no child
		if (root->left == NULL)
		{
			struct data *temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			struct data *temp = root->left;
			free(root);
			return temp;
		}

		// node with two children: Get the inorder successor (smallest
		// in the right subtree)
		struct data* temp = minValueNode(root->right);

		// Copy the inorder successor's content to this node
		strcpy(root->Name, temp->Name);
		strcpy(root->Company, temp->Company);
		strcpy(root->Address, temp->Address);
		strcpy(root->Zipcode, temp->Zipcode);
		strcpy(root->Phones, temp->Phones);
		strcpy(root->Email, temp->Email);

		// Delete the inorder successor
		root->right = deleteNode(root->right, temp->Name);
	}
	return root;
}
*/

struct data* deleteNode(struct data* root, char* key) {
	struct data* x = NULL;
	struct data* y = NULL;
	struct data* z = NULL;
	z = search(root, key);

	if (z->left == NULL || z->right == NULL) {
		y = z;
	}
	else {
		y = inOrderSuccessor(root, z);
	}
	if (y->left != NULL)
		x = y->left;
	else
		x = y->right;
	if (x != NULL)
		x->parent = y->parent;
	if (y->parent == NULL)
		root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;
	if (y != z) {
		strcpy(z->Name, y->Name);
		strcpy(z->Company, y->Company);
		strcpy(z->Address, y->Address);
		strcpy(z->Zipcode, y->Zipcode);
		strcpy(z->Phones, y->Phones);
		strcpy(z->Email, y->Email);
	}
	return y;
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
	while (1) {
		if (str[i] != ' ') {
			for (int j = 0; j < len - i; j++)
				str[j] = str[i + j];
			str[len - 1] = NULL;
			break;
		}
		else
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
		//printf("%c", c);
		//printf("c = %c", c);
		if (c == '|' || c == 10) {
			//printf("\n\ncdata : %s'\n\n", cData);
			trim(cData);
			//printf("a\n\ntc cdat : %s'\n\n", cData);
			return 0;
		}
		cData[j++] = c;
		//printf("%s\n", cData);
		//printf("\n\n");
	}
	return 0;
}

int InputData(FILE* fi, struct data* data) {
	int i, j = 0;

	for (i = 0; i<6; i++) {
		if (i == 0)
			InputDataToCArray(fi, data->Name, i);
		else if (i == 1) {
			InputDataToCArray(fi, data->Company, i);
				//printf("\n\n%s\n\n", data->Company);
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

int index = 0;
void printNode(struct data* root) {
	if (root) {
		printf("%d%s\n", index,root->Name);
		printf("	Company: %s\n", root->Company);
		printf("	Address: %s\n", root->Address);
		printf("	Zipcode: %s\n", root->Zipcode);
		printf("	Phones: %s\n", root->Phones);
		printf("	Email: %s\n", root->Email);
	}
	else
		printf("root is Empty!\n");
}

void inorder(struct data *root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printNode(root);
		index++;
		inorder(root->right);
	}
}

void saveInorder(struct data *root, FILE* fo)
{
	if (root != NULL)
	{
		saveInorder(root->left, fo);
		fprintf(fo, "%.30s | %.50s | %.40s | %.50s | %.50s | %.50s \n", root->Name, root->Company, root->Address
			, root->Zipcode, root->Phones, root->Email);
		saveInorder(root->right, fo);
	}
	//else
//		fprintf(fo, "%c", EOF);
}

int main() {
	FILE *fi;
	struct data* dataArr[MAXDATANUM];
	struct data* root = NULL;
	int i, s = 0;
	char command[MAXCOM];
	char* cmd;
	char c;

	while (1) {
		fgets(command, MAXCOM, stdin);
		command[strlen(command) - 1] = NULL;
		if (command[0] == 'r') {
			i = 0;
			cmd = strrchr(command, ' ') + 1;
			fi = fopen(cmd, "r");

			int a = 0;
			while (1) {
				fscanf(fi, "%c", &c);
				//	printf("%d ", c);
				if (c == EOF)
					break;
				if (c == 10) {
					if (a != 0)
						break;
					s++;
					a++;
				}
				else
					a = 0;

			}
			printf("%d\n", s);
			//한명의 데이터가 끝나면 ASCII CODE 10이 나온다. 10 = LINE FEED
			//한명의 데이터는 |, 즉 ASCII CODE 124로 구분된다.
			fseek(fi, 0, SEEK_SET);
			for (int i = 0; i < s; i++) {
				struct data* tmp = makeEmptyNode();
				InputData(fi, tmp);
				root = insert(root, tmp);
				//printf("%s\n%s\n%s\n%s\n%s\n%s\n\n", dataArr[i]->Name, dataArr[i]->Company, dataArr[i]->Address, dataArr[i]->Zipcode, dataArr[i]->Phones, dataArr[i]->Email);
			}
			//printf("%s\n", root->Name);
			//500개의 데이터다
		}
		else if (command[0] == 'f') {
			char* a = strrchr(command, ' ') + 1;
			//printf("%s\n", a);
			printNode(search(root, a));
			printf("Ceil = %s\n", Ceil(root, a)->Name);
			printf("Floor = %s\n", Floor(root, a)->Name);
			index = 0;
		}
		else if (command[0] == 't') {
			char* a = strrchr(command, ' ') + 1;
			printNode(trace(root, a));
			index = 0;
		}
		else if (command[0] == 'l') {
			inorder(root);
			index = 0;
		}
		else if (command[0] == 'd') {
			char* a = strrchr(command, ' ') + 1;
			deleteNode(root, a);
		}
		else if (command[0] == 's') {
			char* a = strrchr(command, ' ') + 1;
			FILE* fo = fopen(a, "w");
			saveInorder(root, fo);
			fclose(fo);
		}
		else if (command[0] = 'e')
			break;
	}

}