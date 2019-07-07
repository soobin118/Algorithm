#include<stdio.h>
#include<stdlib.h>
typedef struct node {
	char elem;
	struct node *prev;
	struct node *next;
}node;

node * getnode()	// make memory of the node
{
	node *tmp;
	tmp = (node *)malloc(sizeof(node));
	return tmp;
}

void printList(node *h) {	// print all items in the linked list
	
	node *f;	// flag
	f = h->next;
	while (f->next != NULL)
	{
		printf("%c", f->elem);
		f = f->next;
	}
	printf("\n");
}

char getEntry(node *h, int position) {	// get item which is on the position from the linked list

	node *f;	// flag
	f = h;
	for (int i = 0; i < position; i++)
	{
		f = f->next;

		if (f->next == NULL)
		{
			printf("invalid position\n");
			return NULL;
		}
	}

	return f->elem;
}

void insertNode(node *h, int position, char item) {	// insert the item to linked list
	node *p,*n,*t;
	p = h;
	for (int i = 0; i < position-1; i++)
	{
		p = p->next;

		if (p->next == NULL)
		{
			printf("invalid position\n");
			return;
		}
	}
	n = p->next;
	t = getnode();
	t->elem = item;
	p->next = t;
	t->prev = p;
	n->prev = t;
	t->next = n;
}

void deleteNode(node *h, int position) {	//delete the item which is on the position from linked list
	node *f,*p, *n;
	f = h;
	for (int i = 0; i < position; i++)
	{
		f = f->next;

		if (f-> next == NULL)
		{
			printf("invalid position\n");
			return;
		}
	}
	p = f->prev;
	n = f->next;
	p->next = n;
	n->prev = p;
}

void memoryfree(node *h)
{
	node *f,*p;
	p = h;
	while (p!= NULL)
	{
		f = p;
		p = p->next;
		free(f);
	}
}
int main()
{
	node *h, *t;	// head & trailer
	int n;			// the number of operation
	char op, item;
	int pos;
	h = getnode();
	t = getnode();
	h->elem = NULL;
	h->prev = NULL;
	h->next = t;
	t->elem = NULL;
	t->prev = h;
	t->next = NULL;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("\n%c", &op);
		switch (op)
		{
		case 'A':
			scanf(" %d %c", &pos, &item);
			insertNode(h, pos, item);
			break;
		case 'P':
			printList(h);
			break;
		case 'D':
			scanf(" %d", &pos);
			deleteNode(h, pos);
			break;
		case 'G':
			scanf(" %d", &pos);
			char result = getEntry(h, pos);
			if(result != NULL)
				printf("%c\n", result);
			break;
		default:
			break;
		}
	}

	memoryfree(h);

	return 0;
}