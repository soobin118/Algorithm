#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node {
   int item;
   struct node *left, *right;
}tree;

tree *makenode()//노드만들기
{
   tree *a;
   a = (tree *)malloc(sizeof(tree));
   return a;
}

tree *findnext(tree *root, int a)//값을넣을 다음노드찾기
{
   tree *left = NULL;
   tree *right = NULL;

   if (root) {
      if (root->item == a) // 찾으러던 노드 찾음
         return root;

      left = findnext(root->left, a);
      if (left) // left가 NULL이 아니면
             //탐색 성공하면 left에 찾으려던 노드, 즉 위에서 리턴한 root값이 left에 저장됨
         return left;

      right = findnext(root->right, a);
      if (right) // right가 NULL이 아니면
               //탐색 성공하면 right에 찾으려던 노드, 즉 위에서 리턴한 root값이 right에 저장됨
         return right;
   }

   // 탐색 중 못 찾으면 NULL을 리턴해서 더이상 찾으려던게 없다는 걸 알림
   if (left == NULL)
      return left;
   if (right == NULL)
      return right;
}
void insertnode(tree *root, tree *p, int a, int b, int c)//노드값삽입
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
void search(tree *root, char *c)//탐색함수
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
   scanf("%d", &n);//노드개수
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

   scanf("%d", &s);//탐색횟수
   cnt = 0;
   while (cnt < s)
   {
      scanf("%s", RorL);
      search(root, RorL);
      cnt++;
   }
}