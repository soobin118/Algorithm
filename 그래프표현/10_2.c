#include<stdio.h>
#include<stdlib.h>
struct vertices {
	int name;
};
struct edges {
	int p1,p2;
	int weight;
};
void insertNameV(struct vertices *v)
{
	int i;
	for (i = 0; i < 6; i++)
		v[i].name = i;
}
void insertContentE(struct edges *e)
{
	e[0].p1 = e[1].p1=e[2].p1=e[3].p1=1;
	e[0].p2 = 2;
	e[1].p2 = 3;
	e[2].p2 = 4;
	e[3].p2 = 6;
	e[0].weight = e[1].weight=e[2].weight=1;
	e[3].weight = 2;
	e[4].p1 = 2;
	e[4].p2 = 3;
	e[4].weight = 1;
	e[5].p1 = 3;
	e[5].p2 = 5;
	e[5].weight = e[6].weight=4;
	e[6].p1 =e[6].p2= 5;
	e[7].p1 = 5;
	e[7].p2 = 6;
	e[7].weight = 3;
}
void makematrix(int **ad, struct edges *e) {
	int i, j, k;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			for (k = 0; k < 8; k++)
			{
				if ((e[k].p1 == i + 1 && e[k].p2 == j + 1) || (e[k].p1 == j + 1 && e[k].p2 == i + 1))
				{
					ad[i][j] = k;
					ad[j][i] = k;
					break;
				}
			}
			
		}
	}

}
void print(int **ad, int n,struct edges *e)
{
	int i;
	if (n > 6)
	{
		printf("-1\n");
		return;
	}
	for (i = 0; i < 6; i++)
	{
		if (ad[n-1][i] != -1)
		{
			printf(" %d %d", i + 1, e[ad[n-1][i]].weight);
		}
	}
	printf("\n");
}
void change(int **ad,int a, int b, int n,struct edges *e,int *ep)
{
	int i;
	if (a > 6 || b > 6)
	{
		printf("-1\n");
		return;
	}
	if (ad[a-1][b-1] != -1)
	{
		for (i = 0; i < *ep; i++)
		{
			if ((e[i].p1 == a &&e[i].p2 == b) || (e[i].p1 == b && e[i].p2 == a))
			{
				if (n != 0)
				{
					e[i].weight = n;
					return;
				}
				else
				{
					ad[a-1][b-1] = ad[b-1][a-1] = -1;
					return;
				}
			}
		}
	}
	else
	{
		for (i = 0; i < *ep; i++)
		{
			if ((e[i].p1 == a &&e[i].p2 == b) || (e[i].p1 == b && e[i].p2 == a))
			{
				if (n != 0)
				{
					e[i].weight = n;
					ad[a - 1][b - 1] = ad[b - 1][a - 1] = i;
					return;
				}
			}
		}
		if(n!=0)
		{
		e[*ep].p1 = a;
		e[*ep].p2 = b;
		e[*ep].weight = n;

		ad[a - 1][b - 1] = ad[b - 1][a - 1] = *ep; 
		*ep += 1;
		}
	}
}
int main()
{
	char f;
	int n, a, b, esize = 8 , *ep = &esize;
	struct vertices v[6];
	struct edges e[21];
	int **ad, i, j;
	ad = (int **)malloc(sizeof(int *) * 6);
	for (i = 0; i < 6; i++)
	{
		ad[i] = (int *)malloc(sizeof(int *) * 6);
	}
	for (i = 0; i < 6; i++)
		for (j = 0; j < 6; j++)
		{
			ad[i][j] = -1;
		}
	insertNameV(v);
	insertContentE(e);
	makematrix(ad, e);
	while (1)
	{
		scanf(" %c", &f);
		switch (f)
		{
		case 'a':
		{
			scanf("%d", &n);
			print(ad,n,e);
			break;
		}
		case 'm':
		{
			scanf("%d%d%d", &a, &b, &n);
			change(ad,a, b, n,e,ep);
			break;
		}
		default:
		{
			return;
		}
		}
	}
	for (i = 0; i < 6; i++)
		free(ad[i]);
	free(ad);
}