#include<stdio.h>
#include<stdlib.h>
struct node {
	int key;
	struct node *next;
};
struct vertices {
	char name;
	int inDegree;
	struct node *outEdges;
	struct node *inEdges;
};
struct edges {
	int start, end;
};
struct graph {
	struct vertices v[100];
	struct edges e[1000];
};

struct graph G;
int n, m;
int *topOrder;

int index(char vName)
{
	int i;
	for (i = 0; i<n; i++)
	{
		if (G.v[i].name == vName)
			return i;
	}
}
void insertVertex(char vName, int i)
{
	G.v[i].name = vName;
	G.v[i].inDegree = 0;
	G.v[i].outEdges = (struct node *)malloc(sizeof(struct node));
	//G.v[i].outEdges=NULL;
	G.v[i].outEdges->next = NULL;
	G.v[i].inEdges = (struct node *)malloc(sizeof(struct node));
	//G.v[i].inEdges=NULL;
	G.v[i].inEdges->next = NULL;
}
void insertFirst(struct node *h, int i)
{
	struct node *a;
	a = (struct node *)malloc(sizeof(struct node));
	a->key = i;
	a->next = h->next;
	h->next = a;
}
void insertDirectedEdge(char uName, char wName, int i)
{
	int uindex, windex;
	uindex = index(uName);
	windex = index(wName);
	G.e[i].start = uindex;
	G.e[i].end = windex;
	insertFirst(G.v[uindex].outEdges, i);
	insertFirst(G.v[windex].inEdges, i);
	G.v[windex].inDegree++;
}
void buildGraph()
{
	int i;
	char vName, uName, wName;

	scanf("%d", &n);
	for (i = 0; i<n; i++)
	{
		scanf(" %c", &vName);
		insertVertex(vName, i);
	}
	scanf(" %d", &m);
	for (i = 0; i<m; i++)
	{
		scanf(" %c %c", &uName, &wName);
		insertDirectedEdge(uName, wName, i);
	}
}
int isEmpty(struct node *h)//0(empty),1(not empty)
{
	if (h->next == NULL) {
		return 1;
	}
	return 0;
}
void enqueue(struct node *h, int x)
{
	struct node *t, *tmp;
	t = (struct node *)malloc(sizeof(struct node));
	t->key = x;
	t->next = NULL;

	if (isEmpty(h))
		h->next = t;
	else {
		tmp = h;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = t;
	}

}
int dequeue(struct node *h)
{
	int r;
	struct node *t;
	r = h->next->key;
	t = h->next;
	h->next = t->next;
	free(t);
	return r;
}
void topologicalSort()//1(DAG),0(non-DAG)
{
	int i, t, in[100], u, w;
	struct node *h, *p;
	topOrder = (int *)malloc(sizeof(int)*(n + 1));
	h = (struct node *)malloc(sizeof(struct node));
	h->next = NULL;

	for (i = 0; i<n; i++)
	{
		in[i] = G.v[i].inDegree;
		if (in[i] == 0)
		{
			enqueue(h, i);
		}
	}
	t = 1;
	while (!isEmpty(h))
	{
		u = dequeue(h);
		topOrder[t] = u;
		t++;
		p = G.v[u].outEdges->next;
		while (p != NULL)
		{
			w = G.e[p->key].end;
			in[w]--;
			if (in[w] == 0)
				enqueue(h, w);
			p = p->next;
		}
	}
	if (t <= n)
		topOrder[0] = 0;
	else
		topOrder[0] = 1;
}
int main()
{
	int i;
	buildGraph();
	topologicalSort();
	if (topOrder[0] == 0)
	{
		printf("0\n");
	}
	else
	{
		for (i = 1; i<=n; i++)
		{
			printf("%c", G.v[topOrder[i]].name);
			if (i == n)
				printf("\n");
			else
				printf(" ");
		}
	}
}