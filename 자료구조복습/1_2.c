#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node {
   int item;
   struct node *left, *right;
}tree;

tree *makenode()//��常���
{
   tree *a;
   a = (tree *)malloc(sizeof(tree));
   return a;
}

tree *findnext(tree *root, int a)//�������� �������ã��
{
   tree *left = NULL;
   tree *right = NULL;

   if (root) {
      if (root->item == a) // ã������ ��� ã��
         return root;

      left = findnext(root->left, a);
      if (left) // left�� NULL�� �ƴϸ�
             //Ž�� �����ϸ� left�� ã������ ���, �� ������ ������ root���� left�� �����
         return left;

      right = findnext(root->right, a);
      if (right) // right�� NULL�� �ƴϸ�
               //Ž�� �����ϸ� right�� ã������ ���, �� ������ ������ root���� right�� �����
         return right;
   }

   // Ž�� �� �� ã���� NULL�� �����ؼ� ���̻� ã�������� ���ٴ� �� �˸�
   if (left == NULL)
      return left;
   if (right == NULL)
      return right;
}
void insertnode(tree *root, tree *p, int a, int b, int c)//��尪����
{
   tree * leftnode = makenode();
   tree * rightnode = makenode();

   p = findnext(root, a);
   if (b != 0) {
      p->left = leftnode;
      leftnode->item = b;
      leftnode->left = NULL;
      leftnode->right = NULL;
   }
   if (c != 0) {
      p->right = rightnode;
      rightnode->item = c;
      rightnode->left = NULL;
      rightnode->right = NULL;
   }
}
void search(tree *root, char *c)//Ž���Լ�
{
   int n, i;
   tree *p = root;
   n = strlen(c);
   printf(" %d", p->item);
   for (i = 0; i < n; i++)
   {
      if (c[i] == 'R')
      {
         p = p->right;
         printf(" %d", p->item);
      }
      else
      {
         p = p->left;
         printf(" %d", p->item);
      }
   }
   printf("\n");
}
int main()
{
   int cnt = 0, n, a, b, c, s;
   char RorL[101];
   tree *root = NULL, *p = NULL;
   scanf("%d", &n);//��尳��
   while (1)
   {
      cnt++;
      scanf("%d%d%d", &a, &b, &c);
      if (root == NULL)
      {
         root = makenode();
         root->item = a;
         root->left = makenode();
         root->left->item = b;
         root->right = makenode();
         root->right->item = c;
      }
      else
      {
         insertnode(root, p, a, b, c);
      }
      if (cnt == n)
         break;
   }

   scanf("%d", &s);//Ž��Ƚ��
   cnt = 0;
   while (cnt < s)
   {
      scanf("%s", RorL);
      search(root, RorL);
      cnt++;
   }
}