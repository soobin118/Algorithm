#include<stdio.h>
#include<stdlib.h>
struct node {
	int ov;
	struct node *next;
};
struct vertices {
	int name;
	int visit;//0=fresh,1=visited
	struct node *h;
};
struct edges {
	int p1, p2;

};
void makeIncidence(struct vertices *v, struct edges *e, int esize, int n)
{
	int i, j, op;
	struct node *p, *prev, *t;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < esize; j++)
		{
			if (e[j].p1 == i + 1 || e[j].p2 == i + 1)
			{
				if (e[j].p1 == i + 1)
					op = e[j].p2;
				else
					op = e[j].p1;

				p = v[i].h->next;
				prev = v[i].h;

				while (p != NULL && p->ov < op)
				{
					prev = p;
					p = p->next;
				}
				t = (struct node *)malloc(sizeof(struct node));
				t->ov = op;
				t->next = p;
				prev->next = t;
			}
		}
	}
}
void DFS(int s, struct vertices *v, int n)
{
	struct node *p;
	int i, cnt = 0;
	for (i = 0; i<n; i++)
	{
		if (v[i].visit == 1)
			cnt++;
	}
	if (cnt == n)
		return;
	if (v[s - 1].visit == 0)
	{
		printf("%d\n", v[s - 1].name);
		v[s - 1].visit = 1;
	}
	p = v[s - 1].h->next;
	while (p != NULL)
	{
		if (v[(p->ov) - 1].visit == 0)
			DFS((p->ov), v, n);
		p = p->next;
	}
}
void freeMemory(struct vertices v)
{
	struct node *prev,*p;
	p = v.h;
	prev = p;
	while (p != NULL)
	{
		prev = p;
		p = p->next;
		free(prev);
	}
}
int main()
{
	int i, n, m, s, ps, pe, j;
	struct vertices v[100];
	struct edges e[1000];
	struct node * tp;

	scanf("%d%d%d", &n, &m, &s);
	for (i = 0; i<n; i++)
	{
		v[i].name = i + 1;
		v[i].visit = 0;
		v[i].h = (struct node *)malloc(sizeof(struct node));
		v[i].h->next = NULL;
	}
	for (i = 0; i<m; i++)
	{
		scanf("%d%d", &ps, &pe);
		e[i].p1 = ps;
		e[i].p2 = pe;
	}

	makeIncidence(v, e, m, n);

	/*for (i = 0; i<n; i++)
	{
	tp = v[i].h->next;
	while (tp !=  NULL)
	{
	if (tp->next != NULL && tp->ov > tp->next->ov)
	printf("%d ", tp->ov);
	tp = tp->next;
	}
	printf("\n");
	}*/

	DFS(s, v, n);
	for (i = 0; i < n; i++)
	{
		freeMemory(v[i]);
	}
}