#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))

typedef struct _node {
	int key;
	struct _node * parent;
	struct _node * left;
	struct _node * right;
	int height;
}node;
node * root;

int isExternal(node * n) {//�ܺγ��� 1��ȯ
	if (n->left == NULL && n->right == NULL)
		return 1;
	else
		return 0;
}
node * sibling(node * v) {//���̳�� ��ȯ
	if (v->parent->left == v)
		return v->parent->right;
	else
		return v->parent->left;
}
node * treeSearch(node * v, int k) {//Ʈ��Ž��
	if (isExternal(v))
		return v;
	if (k == v->key)
		return v;
	else if (k < v->key)
		return treeSearch(v->left, k);
	else
		return treeSearch(v->right, k);
}
void expandExternal(node * w) {
	node * lc = (node *)malloc(sizeof(node));
	node * rc = (node *)malloc(sizeof(node));

	lc->left = NULL;//�����ڽĳ��Ȯ��
	lc->right = NULL;
	lc->parent = w;//�θ��忬��
	lc->height = 0;

	rc->left = NULL;//�������ڽĳ��Ȯ��
	rc->right = NULL;
	rc->parent = w;//�θ��忬��
	rc->height = 0;

	w->left = lc;//�θ��忡 ����
	w->right = rc;
	w->height = 1;//��������
}
int heightUpdateAndBalanceCheck(node * w) {
	node * l, *r;
	int n;

	if (w == NULL)//��Ʈ���� ��ȯ
		return 1;

	l = w->left;
	r = w->right;

	if (!isExternal(l))
		l->height = max(l->right->height, l->left->height) + 1;//��Ʈ����� ���ʳ�带 ��Ʈ�� �ϴ� ��Ʈ���� ���� ����
	if (!isExternal(r))
		r->height = max(r->right->height, r->left->height) + 1;//��Ʈ����� �����ʳ�带 ��Ʈ�� �ϴ� ��Ʈ���� ���� ����

	n = abs(r->height - l->height);//�� ��Ʈ���� ������ ��

	return n < 2;//�����̸� 1 ��ȯ
}
void restructure(node * x) {
	node * y, *z;
	node * a, *b, *c;//x,y,z�� ���� ��ȸ �湮����
	node *T[4];//x,y,z�� ��Ʈ�� �ϴ� ��Ʈ���� ������ 4���� ��Ʈ������ ������ȸ �湮����

	y = x->parent;
	z = y->parent;//z-y-x

	if (z->key < y->key && y->key < x->key) {
		a = z;
		b = y;
		c = x;
		T[0] = a->left;
		T[1] = b->left;
		T[2] = c->left;
		T[3] = c->right;
	}
	else if (x->key < y->key && y->key < z->key) {
		a = x;
		b = y;
		c = z;
		T[0] = a->left;
		T[1] = a->right;
		T[2] = b->right;
		T[3] = c->right;
	}
	else if (z->key < x->key && x->key < y->key) {
		a = z;
		b = x;
		c = y;
		T[0] = a->left;
		T[1] = b->left;
		T[2] = b->right;
		T[3] = c->right;
	}
	else {
		a = y;
		b = x;
		c = z;
		T[0] = a->left;
		T[1] = b->left;
		T[2] = b->right;
		T[3] = c->right;
	}
	//z�ڸ��� b�ֱ�
	if (z == root) {
		root = b;
		b->parent = NULL;
	}
	else if (z->parent->left == z) {//z�� �����ڽ�
		z->parent->left = b;
		b->parent = z->parent;
	}
	else {//z�� �������ڽ�
		z->parent->right = b;
		b->parent = z->parent;
	}
	//b�� ���ʿ� a, b�� �����ʿ� c�� ����, ������ �ڽĵ� ����
	b->left = a;
	a->parent = b;

	a->left = T[0];
	a->right = T[1];
	T[0]->parent = a;
	T[1]->parent = a;

	b->right = c;
	c->parent = b;

	c->left = T[2];
	c->right = T[3];
	T[2]->parent = c;
	T[3]->parent = c;
}
void searchAndRepairAfterInsertion(node * w) {
	node * z, *y, *x;

	z = w;
	while (heightUpdateAndBalanceCheck(z)) {//�θ���� �ö󰡸鼭 ���� ������Ʈ �� �����˻�
		if (z == root)
			return;
		z = z->parent;
	}

	if (z->left->height > z->right->height)//z�� ���� �ڽ� y
		y = z->left;
	else
		y = z->right;

	if (y->left->height > y->right->height)//y�� ���� �ڽ� x
		x = y->left;
	else if (y->left->height < y->right->height)
		x = y->right;
	else
		x = y->left;

	restructure(x);//b�� ��Ʈ�� �ϴ� ��Ʈ���� ��� ��� ���� ����

	while (z != root) {
		heightUpdateAndBalanceCheck(z);
		z = z->parent;
	}
}
void insertItem(int k) {
	node * w = treeSearch(root, k);

	if (!isExternal(w))
		return;
	else {
		w->key = k;//Ű�ְ�
		expandExternal(w);//Ȯ��
		searchAndRepairAfterInsertion(w);
	}
}
void preOrder(node * w) {//������ȸ
	if (isExternal(w))
		return;

	printf(" %d", w->key);
	preOrder(w->left);
	preOrder(w->right);
}
int findElement(int k) {//Ž���Ͽ� Ű����ȯ
	node * w = treeSearch(root, k);

	if (isExternal(w))
		return 0;
	else
		return w->key;
}
node * inOrderSucc(node * w) {//������ȸ ����� ��ȯ
	w = w->right;
	while (w->left != NULL)
		w = w->left;
	return w;
}
void freeFunc(node * w) {//������ȸ ���鼭 free
	if (w == NULL)
		return;
	freeFunc(w->left);
	freeFunc(w->right);
	free(w);
}
int main()
{
	char c;
	int n;
	int find, del;

	root = (node*)malloc(sizeof(node));
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;

	while (1) {
		scanf("%c", &c);
		switch (c) {
		case 'i':
			scanf("%d", &n);
			insertItem(n);
			break;
		case 's':
			scanf("%d", &n);
			find = findElement(n);
			if (find)
				printf("%d\n", find);
			else
				printf("X\n");
			break;
		case 'p':
			preOrder(root);
			printf("\n");
			break;
		case 'q':
			freeFunc(root);
			return;
			break;
		}
	}
	return 0;
}