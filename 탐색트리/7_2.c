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

int isExternal(node * n) {//외부노드면 1반환
	if (n->left == NULL && n->right == NULL)
		return 1;
	else
		return 0;
}
node * sibling(node * v) {//사촌노드 반환
	if (v->parent->left == v)
		return v->parent->right;
	else
		return v->parent->left;
}
node * treeSearch(node * v, int k) {//트리탐색
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

	lc->left = NULL;//왼쪽자식노드확장
	lc->right = NULL;
	lc->parent = w;//부모노드연결
	lc->height = 0;

	rc->left = NULL;//오른쪽자식노드확장
	rc->right = NULL;
	rc->parent = w;//부모노드연결
	rc->height = 0;

	w->left = lc;//부모노드에 연결
	w->right = rc;
	w->height = 1;//높이증가
}
int heightUpdateAndBalanceCheck(node * w) {
	node * l, *r;
	int n;

	if (w == NULL)//루트노드면 반환
		return 1;

	l = w->left;
	r = w->right;

	if (!isExternal(l))
		l->height = max(l->right->height, l->left->height) + 1;//루트노드의 왼쪽노드를 루트로 하는 부트리의 높이 설정
	if (!isExternal(r))
		r->height = max(r->right->height, r->left->height) + 1;//루트노드의 오른쪽노드를 루트로 하는 부트리의 높이 설정

	n = abs(r->height - l->height);//두 부트리의 높이의 차

	return n < 2;//균형이면 1 반환
}
void restructure(node * x) {
	node * y, *z;
	node * a, *b, *c;//x,y,z의 중위 순회 방문순서
	node *T[4];//x,y,z를 루트로 하는 부트리를 제외한 4개의 부트리들의 중위순회 방문순서

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
	//z자리에 b넣기
	if (z == root) {
		root = b;
		b->parent = NULL;
	}
	else if (z->parent->left == z) {//z가 왼쪽자식
		z->parent->left = b;
		b->parent = z->parent;
	}
	else {//z가 오른쪽자식
		z->parent->right = b;
		b->parent = z->parent;
	}
	//b의 왼쪽에 a, b의 오른쪽에 c를 연결, 나머지 자식들 연결
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
	while (heightUpdateAndBalanceCheck(z)) {//부모노드로 올라가면서 높이 업데이트 및 균형검사
		if (z == root)
			return;
		z = z->parent;
	}

	if (z->left->height > z->right->height)//z의 높은 자식 y
		y = z->left;
	else
		y = z->right;

	if (y->left->height > y->right->height)//y의 높은 자식 x
		x = y->left;
	else if (y->left->height < y->right->height)
		x = y->right;
	else
		x = y->left;

	restructure(x);//b를 루트로 하는 부트리의 모든 노드 균형 유지

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
		w->key = k;//키넣고
		expandExternal(w);//확장
		searchAndRepairAfterInsertion(w);
	}
}
void preOrder(node * w) {//선위순회
	if (isExternal(w))
		return;

	printf(" %d", w->key);
	preOrder(w->left);
	preOrder(w->right);
}
int findElement(int k) {//탐색하여 키값반환
	node * w = treeSearch(root, k);

	if (isExternal(w))
		return 0;
	else
		return w->key;
}
node * inOrderSucc(node * w) {//중위순회 계승자 반환
	w = w->right;
	while (w->left != NULL)
		w = w->left;
	return w;
}
void freeFunc(node * w) {//후위순회 돌면서 free
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