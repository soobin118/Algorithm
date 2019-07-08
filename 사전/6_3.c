#include<stdio.h>
void find(int *a, int *b, char c)
{
	if(c=='N')
	{
		*b=((*b)+(*a))/2;
	}
	else
	{
		*a=((*a)+(*b))/2+1;
	}
}
int main()
{
	int a,b,n,*ap=&a,*bp=&b,i;
	char c;
	scanf("%d%d%d",ap,bp,&n);
	for(i=0;i<n;i++)
	{
		scanf(" %c",&c);
		find(ap,bp,c);
	}
	printf("%d\n",*ap);
}