#include<stdio.h>
#include<stdlib.h>

struct vertices {
	int name;
	int visit;//0=fresh, 1=visited
};
struct edges {
	int p1, p2;
};
void insertAr(int **ar,struct edges *e,int m,int n)
{
	int i,j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			ar[i][j] = -1;
		}
	}
	for (i = 0; i < m; i++)
	{
		ar[e[i].p1 - 1][e[i].p2 - 1] =ar[e[i].p2-1][e[i].p1-1]= i;
	}
}
void BFS(int s, int n, int **ar,struct vertices *v, struct edges *e)
{
	int queue[100],front=0,end=0,i;

	if (v[s - 1].visit == 0)
	{
		printf("%d\n", v[s - 1].name);
		v[s - 1].visit = 1;
	}
	for (i = 0; i < n; i++)
	{
		if (ar[s - 1][i] != -1)
		{
			printf("%d\n", v[i].name);
			v[i].visit = 1;
			queue[end] = i + 1;
			end++;
		}
	}
	while (front!=end)
	{
		for (i = 0; i < n; i++)
		{
			if (ar[queue[front]-1][i] != -1)
			{
				if (v[i].visit == 0)
				{
					printf("%d\n", v[i].name);
					v[i].visit = 1;
					queue[end] = i + 1;
					end++;
				}
			}
		}
		front++;
	}
}
int main()
{
	struct vertices v[100];
	struct edges e[1000];
	int i,n, m, s,ps,pe;
	int **ar;
	scanf("%d%d%d", &n, &m, &s);
	ar = (int **)malloc(sizeof(int *)*n);
	for (i = 0; i < n; i++)
	{
		ar[i] = (int *)malloc(sizeof(int)*n);
	}
	for (i = 0; i < n; i++) {
		v[i].name = i + 1;
		v[i].visit = 0;
	}
	for (i = 0; i < m; i++)
	{
		scanf("%d%d", &ps, &pe);
		e[i].p1 = ps;
		e[i].p2 = pe;
	}
	insertAr(ar, e, m, n);
	BFS(s, n, ar, v, e);
	for (i = 0; i < n; i++)
		free(ar[i]);
	free(ar);
}