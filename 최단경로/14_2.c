#include<stdio.h>
#include<stdlib.h>
typedef struct vertices {
	int name;
	int d;
}vertices;
typedef struct edges {
	int start, end, w;
}edges;

void bellmanford(vertices *v, edges *e, int n, int m, int s) {
	int i,j;
	int u, z;
	for (i = 0; i < n; i++)
	{
		v[i].d = 30 * 1000;//set infinite
	}
	v[s - 1].d = 0;//start
	for (i = 1; i <= n - 1; i++) {
		for (j = 0; j < m; j++) {
			u = e[j].start;
			z = e[j].end;
			if (v[u-1].d!=30*1000 && v[z - 1].d > v[u - 1].d + e[j].w)
				v[z - 1].d = v[u - 1].d + e[j].w;
		}
	}
	for (i = 0; i < n; i++)
	{
		if (i == s - 1)
			continue;
		else if (v[i].d < 30*1000)
		{
			printf("%d %d\n", i + 1, v[i].d);
		}
	}
}
int main()
{
	int n, m,s,i;
	vertices *v;
	edges *e;
	scanf("%d%d%d", &n, &m, &s);
	v = (vertices *)malloc(sizeof(vertices)*n);
	e = (edges *)malloc(sizeof(edges)*m);

	for (i = 0; i < n; i++)
	{
		v[i].name = i + 1;
	}

	for (i = 0; i < m; i++)
	{
		scanf("%d%d%d", &e[i].start, &e[i].end, &e[i].w);
	}
	bellmanford(v, e, n, m,s);
	free(v);
	free(e);
}