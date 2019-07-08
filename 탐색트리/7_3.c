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

int isExternal(node * n) {
   if (n->left == NULL && n->right == NULL)
      return 1;
   else
      return 0;
}
node * sibling(node * v) {
   if (v->parent->left == v)
      return v->parent->right;
   else
      return v->parent->left;
}
node * treeSearch(node * v, int k) {
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

   lc->left = NULL;
   lc->right = NULL;
   lc->parent = w;
   lc->height = 0;

   rc->left = NULL;
   rc->right = NULL;
   rc->parent = w;
   rc->height = 0;

   w->left = lc;
   w->right = rc;
   w->height = 1;
}
int heightUpdateAndBalanceCheck(node * w) {
   node * l, *r;
   int n;

   if (w == NULL)
      return 1;

   l = w->left;
   r = w->right;

   if (!isExternal(l))
      l->height = max(l->right->height, l->left->height) + 1;
   if (!isExternal(r))
      r->height = max(r->right->height, r->left->height) + 1;

   n = abs(r->height - l->height);

   return n < 2;
}
node * restructure(node * x) {
   node * y, * z;
   node * a, * b, * c;
   node * T[4];

   y = x->parent;
   z = y->parent;

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
   
   if (z == root) {
      root = b;
      b->parent = NULL;
   }
   else if (z->parent->left == z) {
      z->parent->left = b;
      b->parent = z->parent;
   }
   else {
      z->parent->right = b;
      b->parent = z->parent;
   }

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

   return b;
}
void searchAndRepairAfterInsertion(node * w) {
   node * z, *y, *x;

   z = w;
   while (heightUpdateAndBalanceCheck(z)) {
      if (z == root)
         return;
      z = z->parent;
   }

   if (z->left->height > z->right->height)
      y = z->left;
   else
      y = z->right;

   if (y->left->height > y->right->height)
      x = y->left;
   else if (y->left->height < y->right->height)
      x = y->right;
   else
      x = y->left;

   restructure(x);

   while (z != root) {
      heightUpdateAndBalanceCheck(z);
      z = z->parent;
   }
}
node * reduceExternal(node * z) {
   node * w = z->parent;
   node * g = w->parent;
   node * zs = sibling(z);
   zs->parent = g;

   if (g == NULL)
      root = zs;

   else {
      if (w == g->left)
         g->left = zs;
      else
         g->right = zs;
   }
   free(z);
   free(w);

   return zs;
}
void insertItem(int k) {
   node * w = treeSearch(root, k);

   if (!isExternal(w))
      return;
   else {
      w->key = k;
      expandExternal(w);
      searchAndRepairAfterInsertion(w);
   }
}
void preOrder(node * w) {
   if (isExternal(w))
      return;

   printf(" %d", w->key);
   preOrder(w->left);
   preOrder(w->right);
}
int findElement(int k) {
   node * w = treeSearch(root, k);

   if (isExternal(w))
      return 0;
   else
      return w->key;
}
node * inOrderSucc(node * w) {
   w = w->right;
   while (w->left != NULL)
      w = w->left;
   return w;
}
void searchAndRepairAfterRemoval(node * w) {
   node * z = w;
   node * y;
   node * x;
   node * b;

   while (heightUpdateAndBalanceCheck(z)) {
      if (z == root)
         return;
      z = z->parent;
   }

   if (z->left->height > z->right->height)
      y = z->left;
   else
      y = z->right;

   if (y->left->height > y->right->height)
      x = y->left;
   else if (y->left->height < y->right->height)
      x = y->right;
   else if (z->left == y)
      x = y->left;
   else
      x = y->right;

   b = restructure(x);

   searchAndRepairAfterRemoval(b);
}
int removeElement(int k) {
   int e;
   node * z, *y;
   node * w = treeSearch(root, k);
   node * zs;

   if (isExternal(w))
      return 0;

   e = w->key;
   z = w->left;
   if (!isExternal(z))
      z = w->right;
   if (isExternal(z))
      zs = reduceExternal(z);
   else {
      z = inOrderSucc(w);
      y = z->parent;
      w->key = y->key;
      zs = reduceExternal(z);
   }
   searchAndRepairAfterRemoval(zs->parent);

   return e;
}
void freeFunc(node * w) {
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
      case 'd':
         scanf("%d", &n);
         del = removeElement(n);
         if (del)
            printf("%d\n", del);
         else
            printf("X\n");
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