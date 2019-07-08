#include<stdio.h>
#include<stdlib.h>
struct node {
	int key;
	struct node *next;
};
void insert(struct node *a, int m,int item)
{
	int i;
	struct node *t,*temp;
	i = item%m;
	if (a[i].next == NULL)
	{
		t = &a[i];
		t->next = (struct node *)malloc(sizeof(struct node));
		t = t->next;
		t->key = item;
		t->next = NULL;
	}
	else
	{
		t = (struct node *)malloc(sizeof(struct node));
		t->key = item;
		temp = a[i].next;
		a[i].next = t;
		t->next = temp;
	}
}
int search(struct node *a, int m,int item)
{
	int i,cnt=1;
	i = item%m;
	struct node *t;
	t = &a[i];
	t=t->next;
	if (t->key == item)
	{
		return 1;
	}
	else {
		while (t->next != NULL)
		{
			t = t->next;
			cnt++;
			if (t->key == item)
			{
				return cnt;
			}
		}
	}
	return 0;
}
int deleteitem(struct node *a,int m, int item)
{
	int d,i,j,flag=0;
	struct node *t,*prev;
	d=search(a, m, item);
	i = item%m;
	t = &a[i];
	while (t->next != NULL)
	{
		prev = t;
		t = t->next;
		if (t->key == item)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		return 0;
	prev->next = t->next;
	return 1;
}
void print(struct node *a,int m)
{
	struct node *t;
	int i;
	for (i = 0; i < m; i++)
	{

			t = &a[i];
			while (t->next != NULL)
			{
				t = t->next;
				printf(" %d", t->key);
			}
	}
	printf("\n");
}

int main()
{
	int m,item,i,sk,dk;
	struct node *a;
	char f;
	scanf("%d", &m);
	a = (struct node *)malloc(sizeof(struct node )*m);
	for (i = 0; i < m; i++)
	{
		a[i].next = NULL;
	}
	while (1)
	{
		scanf(" %c", &f);
		if (f == 'i')
		{
			scanf("%d", &item);
			insert(a,m,item);
		}
		else if (f == 's')
		{
			scanf("%d", &item);
			sk=search(a,m,item);
			printf("%d\n", sk);
		}
		else if (f == 'd')
		{
			scanf("%d", &item);
			dk=deleteitem(a,m, item);
			printf("%d\n", dk);
		}
		else if (f == 'p')
		{
			print(a, m);
		}
		else
			break;
	}
}