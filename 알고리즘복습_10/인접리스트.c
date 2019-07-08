#include<stdio.h>
#include<stdlib.h>

typedef struct edges {
	int ep1;
	int ep2;
	int weight;
}edges;
typedef struct node {
	int elem;
	struct node *next;
}node;
typedef struct vertices {
	int name;
	node *incident;
}vertex;
typedef struct graph {
	edges *edge;
	vertex *vert;
}graph;
void arrange(graph *g, node *w, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (g->edge[g->vert[i].incident->elem].ep1 == i + 1)
		{

		}
		else if(g->edge[g->vert[i].incident->elem].ep2 == i + 1)

	}
}
int main()
{
	graph *g;
	g = (graph *)malloc(sizeof(graph));
	g->vert = (vertex *)malloc(sizeof(vertex)*6);
	for (int i = 0; i < 6; i++)
	{
		g->vert[i].name = i+1;
		g->vert[i].incident = (node *)malloc(sizeof(node));
		g->vert[i].incident->next = NULL;
	}
	g->edge = (edges *)malloc(sizeof(edges) * 21);
	g->edge[0].ep1 = 1;	g->edge[0].ep2 = 2;	g->edge[0].weight = 1;
	g->edge[1].ep1 = 1;	g->edge[1].ep2 = 3;	g->edge[1].weight = 1;
	g->edge[2].ep1 = 1;	g->edge[2].ep2 = 4;	g->edge[2].weight = 1;
	g->edge[3].ep1 = 1;	g->edge[3].ep2 = 6;	g->edge[3].weight = 2;
	g->edge[4].ep1 = 2;	g->edge[4].ep2 = 3;	g->edge[4].weight = 1;
	g->edge[5].ep1 = 3;	g->edge[5].ep2 = 5;	g->edge[5].weight = 4;
	g->edge[6].ep1 = 5;	g->edge[6].ep2 = 5;	g->edge[6].weight = 4;
	g->edge[7].ep1 = 5;	g->edge[7].ep2 = 6;	g->edge[7].weight = 3;
	for (int i = 0; i < 8; i++)
	{
		node *t = (node *)malloc(sizeof(node));
		t->elem = i;
		t->next = NULL;
		if (g->edge[i].ep1 != g->edge[i].ep2)
		{
			node *p = g->vert[g->edge[i].ep1 - 1].incident;
			while (p->next != NULL)
				p = p->next;
			p->next = t;
		}
		node *p = g->vert[g->edge[i].ep2 - 1].incident;
		while (p->next != NULL)
			p = p->next;
		p->next = t;
	}
	char op;
	while (1)
	{
		op = getchar();
		switch (op)
		{
		case 'a':
			break;
		case 'm':
			break;
		case 'q':
			exit(1);
			break;
		default:
			break;
		}
	}
	return 0;
}