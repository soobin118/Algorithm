#include<stdio.h>
#include<stdlib.h>
typedef struct node{
	int key;
	struct node *next;
}node;
typedef struct vertices{
	int name;
	int sort;
	int d;
	node *h;
}vertices;
typedef struct edges{
	int s,e,w;
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

int incidentedgeindex(vertices start, vertices end, edges *e,int m)
{
	int i;
	for(i=0;i<m;i++){
		if(e[i].s==start.name &&e[i].e==end.name)
			return i;
	}
}
void DAGShortestPaths(vertices *v, edges *e, int n, int m, int s)
{
	int i,j,k;
	int enumber;
	node *p;
	for(i=0;i<n;i++)
	{
		v[i].d=200*1000;
	}
	v[s-1].d=0;
	for(k=1;k<=n-1;k++)
	{
	for(i=1;i<=n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(v[j].sort==i)//위상순서
			{
				p=v[j].h->next;
				while(p!=NULL)
				{
					enumber=incidentedgeindex(v[j],v[(p->key)-1],e,m);
					if(v[j].d!=200*1000 && v[(p->key)-1].d>(v[j].d+e[enumber].w))
					{
						v[(p->key)-1].d=(v[j].d+e[enumber].w);
					}
					p=p->next;
				}
			}
		}
	}
	}
	for(i=0;i<n;i++)
	{
		if(v[i].d!=200*1000 && v[i].d!=0)
			printf("%d %d\n", v[i].name, v[i].d);
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
	int n,m,s,i,a,b,j,weight;
	vertices *v;
	edges *e;

	scanf("%d%d%d",&n,&m,&s);
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
		scanf("%d%d%d",&a,&b,&weight);
		e[i].s=a;
		e[i].e=b;
		e[i].w=weight;
		makeIncidence(v,e[i],n);
	}
	for(i=0;i<n;i++)
	{
		scanf("%d",&v[i].sort);
	}

	DAGShortestPaths(v,e,n,m,s);

	free(e);
	for(i=0;i<n;i++)
	{
		freev(v[i]);
	}
	free(v);
}