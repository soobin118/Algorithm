#include<stdio.h>
#include<stdlib.h>
int *heap;
typedef struct node {
	int key;
	struct node *next;
}node;
typedef struct vertices {//��������ü
	int name;
	int d;
	struct node *h;
}vertices;
typedef struct edges {//��������ü
	int p1, p2, w;

}edges;
int opposite(vertices v, edges e)//v�� e�� �̾��� �ݴ��� �����̸� ����
{
	if (e.p1 == v.name)
		return e.p2;
	else if (e.p2 == v.name)
		return e.p1;
	return 0;
}
void makeIncidence(vertices *v, edges *e, int n, int m)//��������Ʈ ����
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
void upHeap(vertices *v, int i)//����
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
void buildHeap(vertices *v, int place)//������
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
	for (i = 1; i <= n; i++)//���� ���
	{
		heap[i] = v[i - 1].name;
		heapsize++;
	}
	while (heapsize > 0)//���� �����������
	{
		minIndex = 1;
		flag = 0;
		for (i = 2; i <= heapsize; i++)
		{
			if (v[heap[minIndex] - 1].d > v[heap[i] - 1].d)
				minIndex = i;//�ּڰ�ã��
		}
		temp = heap[minIndex];
		heap[minIndex] = heap[heapsize];
		heap[heapsize] = temp;//�ּҰ��̶� �� ������ swap
		heapsize--;//�������� -1
		t = v[temp - 1].h->next;//���� temp�� heap[minIndex]����Ǿ�����
		printf(" %d", temp);
		cost += v[temp - 1].d;//��뿡 �賶�� �ִ� ������ d�߰�
		while (t != NULL)
		{
			z = opposite(v[temp - 1], e[t->key]);
			for (i = 1; i <= heapsize; i++)
			{
				if (heap[i] == z)
					flag = 1;//���� ����!
			}
			if (flag == 1)//���� �����ϸ�
			{
				if (v[z - 1].d > e[t->key].w)//������ d�� ����
					v[z - 1].d = e[t->key].w;
			}
			t = t->next;
		}
		buildHeap(v, heapsize);//������
	}
	printf("\n%d\n", cost);
}
void freevertices(struct vertices v)//���� ����
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
	for (i = 0; i < n; i++) {//�����ʱ�ȭ
		v[i].name = i + 1;
		v[i].h = (node *)malloc(sizeof(node));
		v[i].h->next = (node *)malloc(sizeof(node));
		v[i].h->next = NULL;
		v[i].d = 99999999;//����
	}
	for (i = 0; i < m; i++) {//�����ʱ�ȭ
		scanf("%d %d %d", &e[i].p1, &e[i].p2, &e[i].w);
	}
	makeIncidence(v, e, n, m);
	primJarnik(v, e, n, m);
	free(e);//��������
	for (i = 0; i < n; i++)
	{
		freevertices(v[i]);//��������
	}
	free(heap);//������
}