#include<stdio.h>
#include<stdlib.h>
int *heap;
typedef struct node {
	int key;
	struct node *next;
}node;
typedef struct vertices {//정점구조체
	int name;
	int d;
	struct node *h;
}vertices;
typedef struct edges {//간선구조체
	int p1, p2, w;

}edges;
int opposite(vertices v, edges e)//v에 e로 이어진 반대편 정점이름 리턴
{
	if (e.p1 == v.name)
		return e.p2;
	else if (e.p2 == v.name)
		return e.p1;
	return 0;
}
void makeIncidence(vertices *v, edges *e, int n, int m)//인접리스트 생성
{
	int i, j;
	struct node *p, *prev;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (e[j].p1 == i + 1 || e[j].p2 == i + 1)
			{
				p = v[i].h;
				while (p != NULL)
				{
					prev = p;
					p = p->next;
				}
				p = (struct node *)malloc(sizeof(struct node));
				p->key = j;
				p->next = NULL;
				prev->next = p;
			}
		}
	}
}
void upHeap(vertices *v, int i)//업힙
{
	int temp;
	if (i == 1)
	{
		return;
	}
	if (v[heap[i] - 1].d >= v[heap[i / 2] - 1].d)
	{
		return;
	}
	temp = heap[i];
	heap[i] = heap[i / 2];
	heap[i / 2] = temp;
	upHeap(v, i / 2);
}
void buildHeap(vertices *v, int place)//빌드힙
{
	int i;
	for (i = 1; i <= place; i++)
	{
		upHeap(v, i);
	}
}

void primJarnik(vertices *v, edges *e, int n, int m)
{
	int i, heapsize = 0, temp, flag, cost = 0;
	int start = 0, minIndex, z;
	node *t;
	heap = (int *)malloc(sizeof(int)*(n + 1));
	v[start].d = 0;
	for (i = 1; i <= n; i++)//힙에 담기
	{
		heap[i] = v[i - 1].name;
		heapsize++;
	}
	while (heapsize > 0)//힙이 비워질때까지
	{
		minIndex = 1;
		flag = 0;
		for (i = 2; i <= heapsize; i++)
		{
			if (v[heap[minIndex] - 1].d > v[heap[i] - 1].d)
				minIndex = i;//최솟값찾기
		}
		temp = heap[minIndex];
		heap[minIndex] = heap[heapsize];
		heap[heapsize] = temp;//최소값이랑 맨 마지막 swap
		heapsize--;//힙사이즈 -1
		t = v[temp - 1].h->next;//현재 temp에 heap[minIndex]저장되어있음
		printf(" %d", temp);
		cost += v[temp - 1].d;//비용에 배낭에 넣는 정점의 d추가
		while (t != NULL)
		{
			z = opposite(v[temp - 1], e[t->key]);
			for (i = 1; i <= heapsize; i++)
			{
				if (heap[i] == z)
					flag = 1;//힙에 존재!
			}
			if (flag == 1)//힙에 존재하면
			{
				if (v[z - 1].d > e[t->key].w)//정점의 d라벨 갱신
					v[z - 1].d = e[t->key].w;
			}
			t = t->next;
		}
		buildHeap(v, heapsize);//빌드힙
	}
	printf("\n%d\n", cost);
}
void freevertices(struct vertices v)//정점 프리
{
	struct node *prev, *p;
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
	vertices *v;
	edges *e;
	int i, n, m;
	scanf("%d %d", &n, &m);
	v = (vertices *)malloc(sizeof(vertices)*n);
	e = (edges *)malloc(sizeof(edges)*m);
	for (i = 0; i < n; i++) {//정점초기화
		v[i].name = i + 1;
		v[i].h = (node *)malloc(sizeof(node));
		v[i].h->next = (node *)malloc(sizeof(node));
		v[i].h->next = NULL;
		v[i].d = 99999999;//무한
	}
	for (i = 0; i < m; i++) {//간선초기화
		scanf("%d %d %d", &e[i].p1, &e[i].p2, &e[i].w);
	}
	makeIncidence(v, e, n, m);
	primJarnik(v, e, n, m);
	free(e);//간선프리
	for (i = 0; i < n; i++)
	{
		freevertices(v[i]);//정점프리
	}
	free(heap);//힙프리
}