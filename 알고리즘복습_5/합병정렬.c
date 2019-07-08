#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int elem;
	struct node *next;
}node;

void insertNode(node *l, int key)
{
	node *p,*t;
	p = l;
	if (p->elem == 0)	// header
	{
		p->elem = key;
	}
	else {
		while (p->next!= NULL)
			p = p->next;
		t = (node *)malloc(sizeof(node));
		t->elem = key;
		t->next = NULL;
		p->next = t;
	}
}

node* mg_partition(node *l, int k)
{
	node *p;
	p = l;
	for (int i = 0; i < k; i++)
	{
		p = p->next;
	}
	return p;
}

node* merge(node *l1, node *l2,int n1, int n2) {
	node *e;
	e = (node*)malloc(sizeof(node));
	e->elem = 0;
	e->next = NULL;
	while (n1 > 0 && n2 > 0)
	{
		if (l1->elem < l2->elem)
		{
			insertNode(e, l1->elem);
			l1 = l1->next;
			n1--;
		}
		else
		{
			insertNode(e, l2->elem);
			l2 = l2->next;
			n2--;
		}
	}
	while (n1 > 0)
	{
		insertNode(e, l1->elem);
		l1 = l1->next;
		n1--;
	}
	while (n2 > 0)
	{
		insertNode(e, l2->elem);
		l2 = l2->next;
		n2--;
	}
	return e;
}
node* mergeSort(node *l, int n) {
	node *l1,*l2;
	if (n <= 1)
		return l;
	if (n > 1)
	{
		l1 = l;
		l2 = mg_partition(l, n / 2);
		l1 = mergeSort(l1, n/2);
		l2 = mergeSort(l2, n-n/2);
		return merge(l1, l2,  n / 2, n-n / 2);
	}
}

void PrintAndFree(node *h)
{
	node *p,*f;
	p = h;
	while (p != NULL)
	{
		printf(" %d", p->elem);
		f = p;
		p = p->next;
		free(f);
	}
	printf("\n");
}
int main()
{
	int n,key;
	node *h;
	scanf("%d", &n);
	h = (node *)malloc(sizeof(node));
	h->elem = 0;
	h->next = NULL;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &key);
		insertNode(h, key);
	}
	
	h = mergeSort(h, n);
	
	PrintAndFree(h);

	return 0;
}