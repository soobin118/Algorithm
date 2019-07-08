#include<stdio.h>
#include<stdlib.h>
typedef struct node {
	int key;
	struct node *next;
}node;
typedef struct vertices {
	int name;
	int d;
	node *h;
}vertices;
typedef struct edges {
	int p1, p2, w;
}edges;
int *heap;
int opposite(vertices v, edges e) {//return opposite vertice index
	if (e.p1 == v.name)
		return e.p2;
	else if (e.p2 == v.name)
		return e.p1;
}
void upHeap(vertices *v, int i) {//minheap
	int temp;
	if (i == 1)
		return;
	if (v[heap[i] - 1].d >= v[heap[i / 2] - 1].d)
		return;
	temp = heap[i];
	heap[i] = heap[i / 2];
	heap[i / 2] = temp;
	upHeap(v,i / 2);

}
void buildHeap(vertices *v, int place) {
	int i;
	for (i = 1; i <= place; i++)
		upHeap(v, i);
}
void makeIncidence(vertices *v, edges *e,int n, int m){//make incident list
	int i,j;
	node *p,*prev;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (e[j].p1 == v[i].name || e[j].p2 == v[i].name)
			{
				p = v[i].h;
				while (p != NULL) 
				{
					prev = p;
					p = p->next;
				}
				p = (node *)malloc(sizeof(node));
				p->key = j;
				p->next = NULL;
				prev->next = p;
			}
		}
	}
}

int elmentOfQueue(int z,int heapsize) {
	int i;
	for (i = 1; i <= heapsize; i++)
	{
		if (heap[i] == z)
			return i;//if z is an element of queue, return 1
	}
	return 0;//if z is not an element of queue, return 0
}

void dijkstra(vertices *v, edges *e, int n, int m,int s)
{
	int temp,i,heapsize=0,z,index;
	node *p;
	for (i = 0; i < n; i++)
	{
		v[i].d = 21*1000;//put infinite value
	}
	v[s-1].d = 0;//start d clear
	heap = (int *)malloc(sizeof(int)*(n+1));
	for (i = 1; i <= n; i++)
	{
		heap[i] = i;
		heapsize++;
	}
	buildHeap(v, heapsize);

	while (heapsize > 0)//!Q.isEmpty()
	{
		temp = heap[1];
		heap[1] = heap[heapsize];
		heap[heapsize] = temp;
		//temp<-Q.removeMin(),temp is u
		heapsize--;
		p = v[temp-1].h->next;
		while (p != NULL)
		{
			z = opposite(v[temp-1], e[p->key]);
			if (index=elmentOfQueue(z, heapsize) !=0)
			{
				if (v[temp-1].d + e[p->key].w < v[z-1].d) {
					v[z-1].d = v[temp-1].d + e[p->key].w;
					upHeap(v, index);
				}
			}
			p = p->next;
		}
		buildHeap(v, heapsize);
	}
	for (i = 0; i < n; i++)
	{
		if (i == s - 1)
			continue;
		if (v[i].d < 21*1000)
			printf("%d %d\n", i + 1, v[i].d);
	}
}
void freeVertices(vertices v)
{
	node *p,*prev;
	p = v.h;
	while (p != NULL)
	{
		prev = p;
		p = p->next;
		free(prev);
	}
}
int main()
{
	int n, m,s,i;
	vertices *v;
	edges *e;
	scanf("%d%d%d", &n, &m,&s);
	v = (vertices *)malloc(sizeof(vertices)*n);
	e = (edges *)malloc(sizeof(edges)*m);
	for (i = 0; i < n; i++)
	{
		v[i].name = i + 1;
		v[i].h = (node *)malloc(sizeof(node));//Çì´õ
		v[i].h->next = NULL;
	}
	for (i = 0; i < m; i++)
	{
		scanf("%d%d%d", &e[i].p1, &e[i].p2, &e[i].w);
	}
	makeIncidence(v, e, n, m);
	dijkstra(v, e, n, m, s);
	free(e);
	free(heap);
	for (i = 0; i < n; i++)
	{
		freeVertices(v[i]);
	}
}