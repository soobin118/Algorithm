#include<stdio.h>
#include<stdlib.h>
struct node {
	int key;
	struct node *next;
};
struct vertices {
	int name;
	struct node *h;
};
struct edges {
	int p1, p2;
	int weight;
};
void insertNameV(struct vertices *v)
{
	int i;
	for (i = 0; i < 6; i++)
	{
		v[i].name = i;
		v[i].h = (struct node *)malloc(sizeof(struct node));
		v[i].h->next = NULL;
	}
}
void makeIncidence(struct vertices *v,struct edges *e,int *ep)
{
	int i, j; 
	struct node *p,*prev;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < *ep; j++)
		{
			if (e[j].p1 == i + 1|| e[j].p2==i+1)
			{
				p = v[i].h;
				while (p!= NULL)
				{
					prev=p;
					p = p->next;
				}
				p = (struct node *)malloc(sizeof(struct node));
				p->key = j;
				p->next = NULL;
				prev->next=p;
			}
		}
	}
}
void insertContentE(struct edges *e)
{
	e[0].p1 = e[1].p1 = e[2].p1 = e[3].p1 = 1;
	e[0].p2 = 2;
	e[1].p2 = 3;
	e[2].p2 = 4;
	e[3].p2 = 6;
	e[0].weight = e[1].weight = e[2].weight = 1;
	e[3].weight = 2;
	e[4].p1 = 2;
	e[4].p2 = 3;
	e[4].weight = 1;
	e[5].p1 = 3;
	e[5].p2 = 5;
	e[5].weight = e[6].weight = 4;
	e[6].p1 = e[6].p2 = 5;
	e[7].p1 = 5;
	e[7].p2 = 6;
	e[7].weight = 3;
}
void print(struct vertices *v, int n, struct edges *e)
{
	struct node *p;
	if (n > 6)
	{
		printf("-1\n");
		return;
	}
	p = v[n - 1].h->next;
	while (1)
	{
		if (p == NULL)
			break;
		if (e[p->key].p1 != n)
		{
			printf(" %d", e[p->key].p1);
		}
		else
			printf(" %d", e[p->key].p2);
		printf(" %d", e[p->key].weight);
		p=p->next;
	}
	printf("\n");
}
void change(struct vertices *v, int a, int b, int n, struct edges *e,int *ep)
{
	int i,ar;
	struct node *p,*t,*l;
	if (a > 6 || b > 6)
	{
		printf("-1\n");
		return;
	}
	for (i = 0; i < *ep; i++)
	{
		if ((e[i].p1 == a&&e[i].p2 == b) || (e[i].p2 == a && e[i].p1 == b))
		{
			if (e[i].weight != -1)
			{
				if (n != 0)
				{
					e[i].weight = n;
					return;
				}
				else//간선이 있는것을 삭제하려고함
				{
					e[i].weight=-1;

					p=v[a-1].h;
					while(p->next->key!=i)
					{
						p=p->next;
					}
					l=p->next->next;
					p->next=l;
					if(a!=b)
					{
						p=v[b-1].h;
						while(p->next->key!=i)
						{
							p=p->next;
						}
						l=p->next->next;
						p->next=l;
						return;
					}
				}
			}
			else//존재했던 간선이 삭제했다 다시 생기는경우
			{
				if(n!=0)
				{
					e[i].weight=n;

					p=v[a-1].h;
					if(p->next==NULL)
					{
						p->next=(struct node *)malloc(sizeof(struct node));
						t=p;
						p=p->next;
						p->key=i;
						p->next=NULL;
						t->next=p;
					}
					else{
						while(p->next!=NULL && p->next->key<i)
						{
							p=p->next;
						}
						l=p->next;
						t=(struct node *)malloc(sizeof(struct node));
						t->key=i;
						p->next=t;
						t->next=l;
					}
					if(a!=b)
					{
					p=v[b-1].h;
					if(p->next==NULL)
					{
						p->next=(struct node *)malloc(sizeof(struct node));
						t=p;
						p=p->next;
						p->key=i;
						p->next=NULL;
						t->next=p;
					}
					else{
						while(p->next!=NULL && p->next->key<i)
						{
							p=p->next;
						}
						l=p->next;
						t=(struct node *)malloc(sizeof(struct node));
						t->key=i;
						p->next=t;
						t->next=l;
					}
					}
					return;
				}
			}
		}
	}
	//간선이 존재하지 않을경우

	if (n != 0)//간선추가
	{
		e[*ep].p1=a;
		e[*ep].p2=b;
		e[*ep].weight=n;
		p=v[a-1].h;
		if(p->next==NULL)
		{
			p->next=(struct node *)malloc(sizeof(struct node));
			t=p;
			p=p->next;
			p->key=i;
			p->next=NULL;
			t->next=p;
		}
		else{
			if(e[p->next->key].p1==a)
				ar=e[p->next->key].p2;
			else
				ar=e[p->next->key].p1;
			while(p->next!=NULL && ar<b)
			{
				p=p->next;
				if(p->next!=NULL)
				{
				if(e[p->next->key].p1==a)
					ar=e[p->next->key].p2;
				else
					ar=e[p->next->key].p1;
				}
			}
			l=p->next;
			t=(struct node *)malloc(sizeof(struct node));
			t->key=*ep;
			p->next=t;
			t->next=l;
		}
		if(a!=b)
		{
		p=v[b-1].h;
		if(p->next==NULL)
		{
			p->next=(struct node *)malloc(sizeof(struct node));
			t=p;
			p=p->next;
			p->key=i;
			p->next=NULL;
			t->next=p;
		}
		else{
			if(e[p->next->key].p1==a)
				ar=e[p->next->key].p2;
			else
				ar=e[p->next->key].p1;
			while(p->next!=NULL && ar<a)
			{
				p=p->next;
				if(p->next!=NULL)
				{
				if(e[p->next->key].p1==a)
					ar=e[p->next->key].p2;
				else
					ar=e[p->next->key].p1;
				}
			}
			l=p->next;
			t=(struct node *)malloc(sizeof(struct node));
			t->key=*ep;
			p->next=t;
			t->next=l;
		}
		}
		*ep+=1;
	}

}
int main()
{
	char f;
	int n, a, b, esize = 8, *ep = &esize;
	struct vertices v[6];
	struct edges e[21];
	insertNameV(v);
	insertContentE(e);
	makeIncidence(v, e, ep);
	while (1)
	{
		scanf(" %c", &f);
		switch (f)
		{
		case 'a':
			{
				scanf("%d", &n);
				print(v, n, e);
				break;
			}
		case 'm':
			{
				scanf("%d%d%d", &a, &b, &n);
				change(v, a, b, n, e,ep);
				break;
			}
		default:
			{
				return;
			}
		}
	}
}