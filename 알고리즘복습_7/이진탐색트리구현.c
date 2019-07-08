#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int k;
	struct node *p, *l, *r;
}node;
node* sibling(node *a)
{
	if (a->p->l == a)
		return a->p->r;
	else if (a->p->r == a)
		return a->p->l;
}
int isExternal(node *a)
{
	if (a->l == NULL && a->r == NULL)
		return 1;
	else
		return 0;
}
node* treeSearch(node *rt, int key)
{
	if (isExternal(rt))
		return rt;
	if (rt->k == key)
		return rt;
	else if (rt->k < key)
		return treeSearch(rt->r, key);
	else
		return treeSearch(rt->l, key);
}
int findElement(node *r, int key)
{
	node *t = treeSearch(r, key);
	if (isExternal(t))
		return 0;
	else
		return t->k;
}
void expandExternal(node *r)
{
	node *lt = (node *)malloc(sizeof(node));
	node *rt = (node *)malloc(sizeof(node));

	lt->l = NULL;
	lt->r = NULL;
	lt->p = r;

	rt->l = NULL;
	rt->r = NULL;
	rt->p = r;

	r->l = lt;
	r->r = rt;
}
void insertItem(node *r, int key)
{
	node *t = treeSearch(r, key);
	if (isExternal(t))
	{
		t->k = key;
		expandExternal(t);
	}
	else
		return;
}
node * inOrderSucc(node *w)
{
	node *t = w->r;
	while (!isExternal(t))
		t = t->l;
	return t;
}
void reduceExternal(node *rt, node *z)
{
	node *w = z->p;
	node *g = w->p;
	node *zs = sibling(z);
	zs->p = g;
	if (g == NULL)
		rt = zs;
	else {
		if (w == g->l)
			g->l = zs;
		else
			g->r = zs;
	}
	free(z);
	free(w);
}
int removeElement(node * rt, int key)
{
	node *t = treeSearch(rt, key);
	if (isExternal(t))
		return 0;
	int e = t->k;
	node *z = t->l;
	if (!isExternal(z))
		z = t->r;
	if(isExternal(z))
		reduceExternal(rt,z);
	else
	{
		z = inOrderSucc(t);
		node *y = z->p;
		t->k = y->k;
		reduceExternal(rt,z);
	}
	return e;
}
void preOrderSucc(node *rt)
{
	if (isExternal(rt))
		return;
	printf(" %d", rt->k);
	if(rt->l != NULL)
		preOrderSucc(rt->l);
	if(rt->r != NULL)
		preOrderSucc(rt->r);
}
int main()
{
	char op;
	int k,elem;
	node *rt;
	rt = (node *)malloc(sizeof(node));
	rt->p = NULL;
	rt->l = NULL;
	rt->r = NULL;
	while (1) {
		op = getchar();
		switch (op)
		{
		case 'i':
			scanf("%d", &k);
			insertItem(rt, k);
			break;
		case 'd':
			scanf("%d", &k);
			elem = removeElement(rt, k);
			if (elem)
				printf("%d\n", elem);
			else
				printf("X\n");
			break;
		case 's':
			scanf("%d", &k);
			elem = findElement(rt, k);
			if (elem)
				printf("%d\n", elem);
			else
				printf("X\n");
			break;
		case 'p':
			preOrderSucc(rt);
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