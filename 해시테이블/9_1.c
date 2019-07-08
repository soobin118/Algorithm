#include<stdio.h>
#include<stdlib.h>
typedef struct node {
	int key;
	struct node *next;
}node;
void insert(int data, node *hash, int m)
{
	int fi = data%m;
	node *p, *prev, *t;

		p = hash[fi].next;
		prev = &hash[fi];
		t = (node *)malloc(sizeof(node));
		t->key = data;
		t->next = p;
		prev->next = t;
}
int search(int data, node *hash,int m) {
	int i,index=1;
	int fi = data%m;
	node *t;
	t = hash[fi].next;
	while (t != NULL)
	{
		if (t->key == data)
		{
			return index;
		}
		t = t->next;
		index++;
	}
	return 0;
}
int Delete(int data, node *hash,int m)
{
	int s, fi = data%m;
	node *p, *prev;
	s = search(data, hash, m);
	if (s == 0)
		return 0;
	else {
		p=&hash[fi];
		for (int i = 0; i < s; i++)
		{
			prev = p;
			p = p->next;
		}
		prev->next = p->next;
		free(p);
		return s;
	}
}
void print(node *hash,int m)
{
	int i;
	node *p;
	for (i = 0; i < m; i++)
	{
		p = hash[i].next;
		while (p != NULL)
		{
			printf(" %d", p->key);
			p = p->next;
		}
	}
	printf("\n");
}
int main()
{
	node *hash;
	node *p, *prev;
	int m,i,data,s,d;
	char c;
	scanf("%d", &m);
	hash = (node *)malloc(sizeof(node)*m);
	for (i = 0; i < m; i++) {
		hash[i].next = NULL;
	}
	while (1)
	{

		scanf(" %c", &c);
		if (c == 'i')
		{
			scanf("%d", &data);
			insert(data, hash, m);
		}
		else if (c == 's')
		{
			scanf("%d", &data);
			s=search(data, hash, m);
			printf("%d\n", s);
		}
		else if (c == 'd')
		{
			scanf("%d", &data);
			d=Delete(data, hash, m);
			printf("%d\n", d);
		}
		else if (c == 'p')
		{
			print(hash, m);
		}
		else
			break;
	}
	for (i = 0; i < m; i++)
	{
		p =hash[i].next;
		while (p != NULL)
		{
			prev = p;
			p = p->next;
			free(prev);
		}
	}
	free(hash);
}