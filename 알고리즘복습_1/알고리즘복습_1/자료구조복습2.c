#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
	int elem;
	struct node *left, *right;
}node;

node* getnode() {	// allocate the memory to the node
	node *tmp;
	tmp = (node *)malloc(sizeof(node));
	tmp->elem = 0;
	tmp->left = NULL;
	tmp->right = NULL;

	return tmp;
}

node * findNext(node *s, int a){		// find the position which will be inserted
	node *l, *r;
	if (s->elem == a)
		return s;
	if (s->left == NULL && s->right == NULL)
		return NULL;
	if (s->left != NULL)
	{
		l = findNext(s->left, a);
		if (l != NULL)
			return l;
	}
	if (s->right != NULL)
	{
		r = findNext(s->right, a);
		if (r != NULL)
			return r;
	}
}

void insertNode(node *root, int a, int b, int c) {	// insert node to the tree
	node * pos;
	if (root->elem == 0)
	{
		root->elem = a;
		root->left = getnode();
		root->left->elem = b;
		root->right = getnode();
		root->right->elem = c;
	}
	else {
		pos = findNext(root, a);
		pos->left = getnode();
		pos->left->elem = b;
		pos->right = getnode();
		pos->right->elem = c;
	}
}

void searchNode(node *root, char *dir) {	// search node from the tree
	node *f = root;
	int n = strlen(dir);
	printf(" %d", f->elem);

	for (int i = 0; i < n;i++)
	{
		if (dir[i] == 'R')
			f = f->right;
		else                     // dir[i] == 'L'
			f = f->left;
		printf(" %d", f->elem);
	}
	printf("\n");
}

int main()
{
	node * root;
	char dir[101];
	int n,a,b,c;

	root = getnode();

	scanf("%d", &n);	// the number of nodes
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &a, &b, &c);
		insertNode(root, a, b, c);
	}
	scanf("%d", &n);	// search count
	for (int i = 0; i < n; i++)
	{
		scanf("%s", dir);
		searchNode(root,dir);
	}
}