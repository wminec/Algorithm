#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#define MAXCOM 30
#define MAXDATA 300
#define MAXDATANUM 1000
using namespace std;

struct Node
{
	char Name[MAXDATA];
	char Company[MAXDATA];
	char Address[MAXDATA];
	char Zipcode[MAXDATA];
	char Phones[MAXDATA];
	char Email[MAXDATA];
	char color;
	Node *left, *right, *parent;

	// Constructor
	Node()
	{
		left = right = parent = NULL;
		color = 'r';
	}
};

// Class to represent Red-Black Tree
class RBTree
{
private:
	Node* root;
protected:
	void rotateLeft(Node *&, Node *&);
	void rotateRight(Node *&, Node *&);
	void fixInsertion(Node *&, Node *&);
	void delfix(Node *&);
public:
	// Constructor
	RBTree() { 
		root = NULL;
	}
	Node*& getRoot();
	void insert(Node* node);
	Node* del(char* key);
	Node* minValueNode(Node* node);
	Node* successor(Node *p);
	Node* search(Node* node, char* key);
	Node* trace(Node* node, char* key);
	void inorder();
};

int index = 0;
void printNode(Node* root) {
	if (root != NULL) {
		printf("%d %s\n",index, root->Name);
		printf("	Company: %s\n", root->Company);
		printf("	Address: %s\n", root->Address);
		printf("	Zipcode: %s\n", root->Zipcode);
		printf("	Phones: %s\n", root->Phones);
		printf("	Email: %s\n", root->Email);
		if (root->color == 'r')
			printf("	RED NODE\n");
		else
			printf("	BLACK NODE\n");
		printf("	Parent : %s\n", root->parent);
		printf("	Left : %s\n", root->left);
		printf("	Right : %s\n", root->right);
	}
	else
		printf("root is Empty!\n");
}

// A recursive function to do level order traversal
void inorderHelper(Node *root)
{
	if (root == NULL)
		return;

	inorderHelper(root->left);
	printNode(root);
	index++;
	inorderHelper(root->right);
}

Node*& RBTree::getRoot() {
	return root;
}

Node* RBTree::search(Node* node, char* key)
{
	// Base Cases: root is null or key is present at root
	if (node == NULL || strcmp(node->Name, key) == 0)
		return node;

	// Key is greater than root's key
	if (strcmp(node->Name, key) < 0)
		return search(node->right, key);

	// Key is smaller than root's key
	return search(node->left, key);
}

Node* RBTree::trace(Node* node, char* key)
{
	cout << root->Name << endl;
	// Base Cases: root is null or key is present at root
	if (node == NULL || strcmp(node->Name, key) == 0)
		return node;

	// Key is greater than root's key
	if (strcmp(node->Name, key) < 0)
		return search(node->right, key);

	// Key is smaller than root's key
	return search(node->left, key);
}

/* A utility function to insert a new node with given key
in BST */
Node* BSTInsert(Node* root, Node *pt)
{
	/* If the tree is empty, return a new node */
	if (root == NULL)
		return pt;

	/* Otherwise, recur down the tree */
	if (strcmp(root->Name, pt->Name) > 0)
	{
		root->left = BSTInsert(root->left, pt);
		root->left->parent = root;
	}
	else
	{
		root->right = BSTInsert(root->right, pt);
		root->right->parent = root;
	}

	/* return the (unchanged) node pointer */
	return root;
}

void RBTree::rotateLeft(Node *&root, Node *&pt)
{
	Node *pt_right = pt->right;

	pt->right = pt_right->left;

	if (pt->right != NULL)
		pt->right->parent = pt;

	pt_right->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_right;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_right;

	else
		pt->parent->right = pt_right;

	pt_right->left = pt;
	pt->parent = pt_right;
}

void RBTree::rotateRight(Node *&root, Node *&pt)
{
	Node *pt_left = pt->left;

	pt->left = pt_left->right;

	if (pt->left != NULL)
		pt->left->parent = pt;

	pt_left->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_left;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_left;

	else
		pt->parent->right = pt_left;

	pt_left->right = pt;
	pt->parent = pt_left;
}

// This function fixes violations caused by BST insertion
void RBTree::fixInsertion(Node *&root, Node *&pt)
{
	Node *parent_pt = NULL;
	Node *grand_parent_pt = NULL;

	while ((pt != root) && (pt->color != 'b') &&
		(pt->parent->color == 'r'))
	{

		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		/*  Case : A
		Parent of pt is left child of Grand-parent of pt */
		if (parent_pt == grand_parent_pt->left)
		{

			Node *uncle_pt = grand_parent_pt->right;

			/* Case : 1
			The uncle of pt is also red
			Only Recoloring required */
			if (uncle_pt != NULL && uncle_pt->color == 'r')
			{
				grand_parent_pt->color = 'r';
				parent_pt->color = 'b';
				uncle_pt->color = 'b';
				pt = grand_parent_pt;
			}

			else
			{
				/* Case : 2
				pt is right child of its parent
				Left-rotation required */
				if (pt == parent_pt->right)
				{
					rotateLeft(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
				pt is left child of its parent
				Right-rotation required */
				rotateRight(root, grand_parent_pt);
				swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}

		/* Case : B
		Parent of pt is right child of Grand-parent of pt */
		else
		{
			Node *uncle_pt = grand_parent_pt->left;

			/*  Case : 1
			The uncle of pt is also red
			Only Recoloring required */
			if ((uncle_pt != NULL) && (uncle_pt->color == 'r'))
			{
				grand_parent_pt->color = 'r';
				parent_pt->color = 'b';
				uncle_pt->color = 'b';
				pt = grand_parent_pt;
			}
			else
			{
				/* Case : 2
				pt is left child of its parent
				Right-rotation required */
				if (pt == parent_pt->left)
				{
					rotateRight(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
				pt is right child of its parent
				Left-rotation required */
				rotateLeft(root, grand_parent_pt);
				swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}
	}

	root->color = 'b';
}

// Function to insert a new node with given data
void RBTree::insert(Node* node)
{
	// Do a normal BST insert
	root = BSTInsert(root, node);

	// fix Red Black Tree violations
	fixInsertion(root, node);
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

/*
Node* RBTree::successor(Node *p)
{
	Node *y = NULL;
	if (p->left != NULL)
	{
		y = p->left;
		while (y->right != NULL)
			y = y->right;
	}
	else
	{
		y = p->right;
		while (y->left != NULL)
			y = y->left;
	}
	return y;
}*/

Node* RBTree::minValueNode(Node* node)
{
	Node* current = node;

	//loop down to find the leftmost leaf
	while (current->left != NULL)
		current = current->left;

	return current;
}

Node* RBTree::successor(Node *n)
{
	// step 1 of the above algorithm 
	if (n->right != NULL)
		return minValueNode(n->right);

	// step 2 of the above algorithm
	Node* p = n->parent;
	while (p != NULL && n == p->right)
	{
		n = p;
		p = p->parent;
	}
	return p;
}

Node* RBTree::del(char* key)
{
	if (root == NULL)
	{
		cout << "\nEmpty Tree.";
		return NULL;
	}
	Node *p;
	Node *y = NULL;
	Node *q = NULL;
	int s = 0;
	char c;
	p = search(root, key);
	if (p == NULL)
	{
		cout << "\nElement Not Found.";
		return NULL;
	}
	else
	{
		//cout << p->Name << endl;
		if (p->left == NULL || p->right == NULL)
			y = p;
		else {
			y = successor(p);
			c = p->color;
			s = 1;
		}
	//	cout << "p name" << p->Name << endl << "y name " << y->Name << endl;
		if (y->left != NULL)
			q = y->left;
		else
		{
			if (y->right != NULL)
				q = y->right;
			else
				q = NULL;
		}
		if (q != NULL)
			q->parent = y->parent;
		if (y->parent == NULL)
			root = q;
		else
		{
			if (y == y->parent->left)
				y->parent->left = q;
			else
				y->parent->right = q;
		}
		/*cout << "q : " << q << endl;
		cout << "p name " << p->Name << endl << "y name " << y->Name << endl;
		cout << "yp name " << y->parent->Name << endl;*/
		if (y != p)
		{
			//p->color = y->color;

			//p->key = y->key;
			strcpy(p->Name, y->Name);
			strcpy(p->Company, y->Company);
			strcpy(p->Address, y->Address);
			strcpy(p->Zipcode, y->Zipcode);
			strcpy(p->Phones, y->Phones);
			strcpy(p->Email, y->Email);
		}
		/*cout << "q : " << q << endl;
		cout << "yp name " << y->parent->Name << endl;
		printf("ypl name %s \n", y->parent->left->Name);
		printf("ypr name %s \n", y->parent->right->Name);
		cout << "p name " << p->Name << endl;
		cout << "asdfasdfas" << root->Name << endl << "y name " << y->Name << endl;
		if (q!=NULL)
			cout << "q name " << q->Name << endl;*/
		
		if (q != NULL && y->color == 'b')
			delfix(q);
		//else if (q == NULL && y->color == 'b')
		//	delfix(y->parent);
		else if (q == NULL) {
			if (s == 0 && y->color == 'b') {
				Node* yp = y->parent;
				y->parent->left = y;
				y->color = 'b';
			//	cout << "yp name " << y->parent->Name << endl;
			//	printf("yl name %s \n", y->left->Name);
			//	printf("yr name %s \n", y->right->Name);
			//	printf("1");
				delfix(y);
				y = yp->left;
				y->parent->left = NULL;
				inorder();
			}
			else if (s==1 && c=='b')
			{
			//	printf("oiuoiuiou\n");
				if (y->right == NULL) {
			//		cout << "yp name " << y->parent->Name << endl;
			//		printf("yl name %s \n", y->left->Name);
			//		printf("yr name %s \n", y->right->Name);
			//		printf("A");
					delfix(y->parent);
			//		cout << "yp name " << y->parent->Name << endl;
		//			printf("yl name %s \n", y->left->Name);
			//		printf("yr name %s \n", y->right->Name);
			//		printf("%s", y->parent);
					//inorder();
				}
				else {
					delfix(y->parent->left);
				}
				
			}
		}
	}
	return y;
	//printf("\n\n\n%c  %s  \n\n", p->color, p->Name);
	//inorder();
}

void RBTree::delfix(Node *&p)
{
/*	cout << "p name " << p->Name << endl;
	cout << "pp name " << p->parent->Name << endl;
	if (p->left != NULL)
		cout << "pl name " << p->left->Name << endl;
	if (p->right != NULL)
		cout << "pr name " << p->right->Name << endl;
	if (p->parent->left != NULL)
		cout << "ppl name " << p->parent->left->Name << endl;
	if (p->parent->right != NULL)
		cout << "ppr name " << p->parent->right->Name << endl;*/
	Node *s;
	while (p != root && p->color == 'b')
	{
	//	printf("0");
	//	inorder();
		if (p->parent->left == p)
		{
		//	printf("1");
			
			s = p->parent->right;
		//	printf("%s", s);
		//	printf("2");
			if (s != NULL && s->color == 'r')
			{
				s->color = 'b';
				p->parent->color = 'r';
		//		printf("3");
				rotateLeft(root, p->parent);
		//		inorder();
				s = p->parent->right;
		//		printf("4");
			}
		//	printf("5");
		//	printf("%s\n", s);
			if (s == NULL) {
				p = p->parent;
				//p->color = 'b';
				continue;
			}
		//	cout << "s name " << s->Name << endl;
			if (s->left == NULL && s->right == NULL || s->left->color == 'b' && s->right->color == 'b')
			{
		//		printf("6");
				s->color = 'r';
				p = p->parent;
			}
			else
			{
				if (s->right == NULL || s->right->color == 'b')
				{
		//			printf("ff");
					s->left->color = 'b';
					s->color = 'r';
					rotateRight(root, s);
		//			inorder();
					s = p->parent->right;
					//	printf("p : %s s : %s\n",p, s);
				}
				s->color = p->parent->color;
				p->parent->color = 'b';
				s->right->color = 'b';
				rotateLeft(root, p->parent);
			//	inorder();
				p = root;
			}
		//	printf("7");
		}
		else
		{
			s = p->parent->left;
			if (s != NULL && s->color == 'r')
			{
				s->color = 'b';
				p->parent->color = 'r';
				rotateRight(root, p->parent);
				s = p->parent->left;
			}
			if (s == NULL) {
				p = p->parent;
		//		p->color = 'b';
				continue;
			}
			if (s->left == NULL && s->right == NULL || s->left->color == 'b' && s->right->color == 'b')
			{
				s->color = 'r';
				p = p->parent;
			}
			else
			{
				if (s->left == NULL || s->left->color == 'b')
				{
					s->right->color = 'b';
					s->color = 'r';
					rotateLeft(root, s);
					s = p->parent->left;
				}
				s->color = p->parent->color;
				p->parent->color = 'b';
				s->left->color = 'b';
				rotateRight(root, p->parent);
				p = root;
			}
		}
		//cout << "aaaaaaa" << root->Name << endl;
		//p->color = 'b';
		//root->color = 'b';
	}
	//cout << "aaaaaaa" << p->Name << endl;
	//root->color = 'b';
	p->color = 'b';
	//printf("\n\n%c\n\n", p->color);
}

// Function to do inorder and level order traversals
void RBTree::inorder() { inorderHelper(root); }

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

int InputData(FILE* fi, Node* data) {
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

// Driver Code
int main()
{
	RBTree tree;

	/*tree.insert(7);
	tree.insert(6);
	tree.insert(5);
	tree.insert(4);
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);
	cout << "Inoder Traversal of Created Tree\n";
	tree.inorder();*/

	FILE *fi;
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
			for (int i = 0; i < 20; i++) {
				Node* tmp = new Node();
				InputData(fi, tmp);
				//printf("aa");
				//root = insert(root, tmp);
				tree.insert(tmp);
				//printf("%s\n", tmp->Name);
				//printf("bb");
				//printf("%s\n%s\n%s\n%s\n%s\n%s\n\n", tmp->Name, tmp->Company, tmp->Address, tmp->Zipcode, tmp->Phones, tmp->Email);
				//printf("%s\n", root->Name);
			}
			//printf("%s\n", root->Name);
			//500개의 데이터다
			//printf("\n%s\n", root->Name);
		}
		else if (command[0] == 'f') {
			char* a = strrchr(command, ' ') + 1;
			//printf("%s\n", a);
			printNode(tree.search(tree.getRoot(), a));
			index = 0;
		}
		else if (command[0] == 't') {
			char* a = strrchr(command, ' ') + 1;
			printNode(tree.trace(tree.getRoot(), a));
			index = 0;
		}
		else if (command[0] == 'l') {
			tree.inorder();
			index = 0;
		}
		else if (command[0] == 'd') {
			char* a = strrchr(command, ' ') + 1;
			tree.del(a);
		}/*
		else if (command[0] == 's') {
			char* a = strrchr(command, ' ') + 1;
			FILE* fo = fopen(a, "w");
			saveInorder(root, fo);
			fclose(fo);
		}*/
		else if (command[0] = 'e')
			break;
	}

	return 0;
}
