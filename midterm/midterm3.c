#include<stdio.h>
#include<stdlib.h>
typedef struct node{
	int k;
	struct node *l,*r,*p;
};
int isExternal(struct node *a)
{
	if(a->l==NULL && a->r==NULL)
		return 1;
	else
		return 0;
}
void expandExternal(struct node *a)
{
	struct node *lp=(struct node *)malloc(sizeof(struct node));
	struct node *rp=(struct node *)malloc(sizeof(struct node));
	lp->l=NULL;
	lp->r=NULL;
	rp->l=NULL;
	rp->r=NULL;
	lp->p=a;
	rp->p=a;
	a->l=lp;
	a->r=rp;
}
struct node *search(struct node *a,int key)
{
	struct node *t;
	t=a;
	if(isExternal(a))
		return a;
	while(!isExternal(t))
	{
		if(t->k <= key)
			t=t->r;
		else
			t=t->l;
	}
	return t;
}
void insertItem(struct node *a, int key)
{
	struct node *t;
	t=search(a, key);
	if(isExternal(t))
	{
		t->k=key;
		expandExternal(t);
	}
}
void print(struct node *a)
{
	if(isExternal(a))
		return;

	printf(" %d",a->k);
	print(a->l);
	print(a->r);
}
int main()
{
	struct node *a;
	int n,k,i;
	scanf("%d",&n);
	a=(struct node*)malloc(sizeof(struct node));
	a->l=NULL;
	a->r=NULL;
	for(i=0;i<n;i++)
	{
		scanf("%d",&k);
		insertItem(a,k);
	}
	print(a);
	printf("\n");
	free(a);
}