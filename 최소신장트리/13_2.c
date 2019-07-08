#include<stdio.h>
#include<stdlib.h>
typedef struct vertices {
	int name;
}vertices;
typedef struct edges {
	int p1, p2, w;
}edges;

int *sack;
int *queue;

void upHeap(edges *e,int i) {
	int temp;
	if (i == 1)
	{
		return;
	}
	if (e[queue[i]].w >= e[queue[i / 2]].w)
		return;
	temp = queue[i];
	queue[i] = queue[i / 2];
	queue[i / 2] = temp;
	upHeap(e, i / 2);
}
void buildHeap(edges *e, int place)
{
	int i;
	for (i = 1; i <= place; i++)
		upHeap(e, i);
}
void kruskal(vertices *v, edges *e,int n, int m)
{
	int i,temp,queuesize=0,cost=0;
	int treecount = 0,u,z,sacknumber;
	sack = (int *)malloc(sizeof(int)*(n+1));
	queue = (int *)malloc(sizeof(int)*(m+1));
	for (i = 0; i < n; i++)
	{
		sack[v[i].name] = i;//배낭번호저장
	}
	for (i = 1; i <= m; i++)
	{
		queue[i] = i-1;//정렬된간선의 인덱스 저장
		queuesize++;
	}
	while (treecount < n - 1)
	{
		temp = queue[1];
		queue[1] = queue[queuesize];
		queue[queuesize] = temp;
		queuesize--;
		//현재 temp==(u,z)의 index
		u = e[temp].p1;
		z = e[temp].p2;
		if (sack[u] != sack[z])//merge
		{
			sacknumber = sack[z];
			for (i = 1; i <= n; i++)
			{
				if (sack[i] == sacknumber)
					sack[i] = sack[u];
			}
			treecount++;
			printf(" %d", e[temp].w);
			cost += e[temp].w;
		}
		buildHeap(e, queuesize);
	}
	printf("\n%d\n", cost);
}
int main()
{
	vertices *v;
	edges *e;
	int n, m, i, j=0,k;
	int point1, point2, weight;
	scanf("%d%d", &n, &m);
	v = (vertices *)malloc(sizeof(vertices)*n);
	e = (edges *)malloc(sizeof(edges)*m);

	for (i = 0; i < n; i++)//정점설정
	{
		v[i].name = i + 1;
	}

	for (i = 0; i < m; i++)//간선정보받고 정렬
	{
		scanf("%d%d%d", &point1, &point2, &weight);
		for (j = 0; j < i; j++)
		{
			if (e[j].w>=weight)
			{
				for (k = i; k > j; k--)
				{
					e[k] = e[k-1];
				}
				break;
			}
		}
		e[j].p1 = point1;
		e[j].p2 = point2;
		e[j].w = weight;
	}
	kruskal(v, e, n, m);
	free(v);
	free(e);
	free(sack);
	free(queue);
}