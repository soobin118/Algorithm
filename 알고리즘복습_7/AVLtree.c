#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int key, height;
	struct node *left, *right, *parent;
}node;
int isExternal(node *w)
{
	if (w->left == NULL && w->right == NULL)
		return 1;
	else
		return 0;
}
void rightRotate(node *y, node *g)
{
	y->parent = g->parent;
	g->left = y->right;
	y->right = g;
	g->parent = y;
}
void leftRotate(node *y, node *g)
{
	y->parent = g->parent;
	g->right = y->left;
	y->left = g;
	g->parent = y;
}
node * restructure(node *x)
{
	node *y = x->parent;
	node *g = y->parent;
	if (y == NULL)
		return y;
	if (g == NULL)
	{
		if (x == y->left)
		{
			x->parent = NULL;
			y->left = x->right;
			x->right = y;
			y->parent = x;
		}
		else
		{
			x->parent = NULL;
			y->right = x->left;
			x->left = y;
			y->parent = x;
		}
		return g;
	}
	if (x == y->left && y == g->left)
	{
		rightRotate(y, g);
	}
	else if (x == y->right && y == g->right)
	{
		leftRotate(y, g);
	}
	else if (x == y->left && y == g->right)
	{
		rightRotate(x,y);
		leftRotate(x, g);
	}
	else    // x == y->right && y == g->left
	{
		leftRotate(x, y);
		rightRotate(x, g);
	}
	return x;
}
int getHeight(node *w)
{
	if (w->parent == NULL)
		return 0;
	if (isExternal(w))
		return w->height;
	return 1 + max(getHeight(w->left), getHeight(w->right));
}
int isBalanced(node *r)
{
	int lh, rh;
	lh = getHeight(r->left);
	rh = getHeight(r->right);
	if (abs(lh - rh) <= 1)
		return 1;
	return 0;
}
int updateHeight(node *w)
{
	if (w->parent == NULL)
		w->height = 0;
	else {
		w->height = w->parent->height + 1;
		w->left->height = w->height;
		w->right->height = w->height;
	}
}
void searchAndFixAfterInsertion(node *w)
{
	node *t = w->parent;
	if (t == NULL)
		return;
	while (t->parent!= NULL) {
		if (!isBalanced(t))
		{
			t = restructure(w);
		}
		else
			t = t->parent;
	}
}
void expandExternal(node *w)
{
	node *lp = (node*)malloc(sizeof(node));
	node *rp = (node*)malloc(sizeof(node));
	
	lp->left = NULL;
	lp->right = NULL;
	lp->parent = w;

	rp->left = NULL;
	rp->right = NULL;
	rp->parent = w;

	w->left = lp;
	w->right = rp;

}
node* treeSearch(node *r, int k)
{
	if (isExternal(r))
		return r;
	if (r->key == k)
		return r;
	else if (r->key > k)
		return treeSearch(r->left, k);
	else
		return treeSearch(r->right, k);
}
void insertItem(node *r, int k)
{
	node *w = treeSearch(r, k);
	if (!isExternal(w))
		return;
	w->key = k;
	expandExternal(w);
	updateHeight(w);
	searchAndFixAfterInsertion(w);
}
void preOrderSucc(node *r)
{
	if (isExternal(r))
		return;
	printf(" %d", r->key);
	preOrderSucc(r->left);
	preOrderSucc(r->right);
}
int main()
{
	int k;
	node *root;
	root = (node *)malloc(sizeof(node));
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;
	root->height = 0;

	char op;
	while (1)
	{
		op = getchar();
		switch (op)
		{
		case 'i':
			scanf("%d", &k);
			insertItem(root, k);
			break;
		case 's':
			scanf("%d", &k);
			node *tmp = treeSearch(root, k);
			if (isExternal(tmp))
				printf("X\n");
			else
				printf("%d\n", tmp->key);
			break;
		case 'p':
			preOrderSucc(root);
			printf("\n");
			break;
		case 'q':
			exit(1);
			break;
		default:
			break;
		}
	}

	return 0;
}