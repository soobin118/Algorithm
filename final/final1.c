#include<stdio.h>
#include<stdlib.h>
typedef struct node{
	int key;
	struct node *next;
}node;
typedef struct vertices{
	int name;
	node *h;
}vertices;
typedef struct edges{
	int s,e;
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
	int n,m,i,a,b;
	vertices *v;
	edges *e;
	node *p;
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
	for(i=0;i<n;i++)
	{
		p=v[i].h->next;
		printf("%d",v[i].name);
		while(p!=NULL)
		{
			printf(" %d",p->key);
			p=p->next;
		}
		printf("\n");
	}
	for(i=0;i<n;i++)
	{
		freev(v[i]);
	}
	free(e);
	free(v);
}