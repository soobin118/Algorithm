#include<stdio.h>
#include<stdlib.h>
typedef struct node{
	int key;
	struct node *next;
}node;
typedef struct vertices{
	int name;
	int l;
	int sort;
	node *h;
}vertices;
typedef struct edges{
	int s,e,l;
}edges;
void makeIncidence(vertices *v, edges e,int n){
	int i,op;
	node *p,*prev,*t;
	for(i=0;i<n;i++)
	{
		if(e.s==v[i].name)
		{
			op=e.e;
			p=v[i].h->next;
			prev=v[i].h;
			while(p!=NULL && p->key<=op)
			{
				prev=p;
				p=p->next;
			}
			t=(node *)malloc(sizeof(node));
			t->key=op;
			t->next=p;
			prev->next=t;
		}
	}
}
void TPSortDFS(vertices *v, int n,int m){
	int i;
	int num;
	num=n;
	for(i=0;i<n;i++)
	{
		v[i].l=0;
	}
	for(i=0;i<n;i++)
	{
		if(v[i].l==0)
		{
			num=rTPSortDFS(v,i,num);
		}
	}
}
int rTPSortDFS(vertices *v, int i,int n){
	node *p;
	v[i].l=1;
	p=v[i].h;
	while(p->next!=NULL)
	{
		p=p->next;
		if(v[(p->key)-1].l==0)
		{
			n=rTPSortDFS(v,(p->key)-1,n);
		}
	}
	v[i].sort=n;
	n-=1;
	return n;
}
void freev(vertices v)
{
	node *p,*prev;
	p=v.h;
	while(p!=NULL)
	{
		prev=p;
		p=p->next;
		free(prev);
	}
}
int main()
{
	int n,m,a,b,i,j;
	vertices *v;
	edges *e;
	scanf("%d%d",&n,&m);
	v=(vertices *)malloc(sizeof(vertices)*n);
	e=(edges *)malloc(sizeof(edges)*m);
	for(i=0;i<n;i++)
	{
		v[i].name=i+1;
		v[i].h=(node *)malloc(sizeof(node));
		v[i].h->next=NULL;
	}
	for(i=0;i<m;i++)
	{
		scanf("%d%d",&a,&b);
		e[i].s=a;
		e[i].e=b;
		makeIncidence(v,e[i],n);
	}
	TPSortDFS(v,n,m);
	for(i=1;i<=n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(v[j].sort==i)
				printf("%d\n",v[j].name);
		}
	}

	free(e);
	for(i=0;i<n;i++)
	{
		freev(v[i]);
	}
	free(v);
}