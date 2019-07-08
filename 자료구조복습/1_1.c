#include<stdio.h>
#include<stdlib.h>
struct node {
	char elem;
	struct node *prev, *next;
};
int size = 0;
void add(struct node *h, int position, char item)//item넣기
{
	struct node *temp, *p = h;
	int i;
	if (position>size + 1)
	{
		printf("invalid position\n");
		return 0;
	}
	temp = (struct node *)malloc(sizeof(struct node));
	temp->elem = item;
	for (i = 0; i<position; i++)
	{
		p = p->next;
	}
	temp->prev = p->prev;
	p->prev->next = temp;
	p->prev = temp;
	temp->next = p;
	size += 1;
}
void deletef(struct node *h, int position)//item 지우기
{
	struct node *p = h;
	int i;
	if (position>size)//지우라고 언급한 위치가 size보다 클경우 invalid position
	{
		printf("invalid position\n");
		return 0;
	}
	for (i = 0; i<position; i++)
	{
		p = p->next;
	}
	(p->next)->prev = p->prev;
	(p->prev)->next = p->next;
	size -= 1;
	free(p);
}
char get_entry(struct node *h, int position)//포지션값 반환
{
	struct node *p = h;
	int i;
	if (position>size)//포지션이 사이즈보다 클경우
	{
		printf("invalid position\n");
		return 0;
	}
	for (i = 0; i<position; i++)
	{
		p = p->next;
	}
	return p->elem;
}
void print(struct node *h)//모든원소 출력
{
	struct node *p = h;
	p = p->next;
	while (p->elem != NULL)
	{
		printf("%c", p->elem);
		p = p->next;
	}
}
int main()
{
	struct node header, trailer, *h, *t;
	int n, cnt = 0, position;
	char c, item, entry;
	h = &header;
	t = &trailer;
	h->next = t;
	t->prev = h;
	h->elem = NULL;
	t->elem = NULL;
	scanf("%d", &n);
	while (cnt<n)
	{
		scanf(" %c", &c);
		if (c == 'A')
		{
			scanf("%d %c", &position, &item);
			add(h, position, item);
		}
		else if (c == 'D')
		{
			scanf("%d", &position);
			deletef(h, position);
		}
		else if (c == 'G')
		{
			scanf("%d", &position);
			entry = get_entry(h, position);
			if (entry != 0)
			{
				printf("%c\n", entry);
			}
		}
		else
		{
			print(h);
			printf("\n");
		}
		cnt++;
	}
}
