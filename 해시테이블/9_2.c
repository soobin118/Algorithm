#include<stdio.h>
#include<stdlib.h>
int insert(int *a, int m,int n,int item)
{
	int i,j;
	i=item%m;
	if(a[i]==0)
	{
		a[i]=item;
		return i;
	}
	else
	{
		for(j=1;j<n;j++)
		{
			printf("C");
			if(a[(i+j)%m]==0)
			{
				a[(i+j)%m]=item;
				return (i+j)%m;
				break;
			}
		}
	}
}
void search(int *a,int m,int n,int item)
{
	int i,j,flag=0;
	i=item%m;
	for(j=0;j<n;j++)
	{
		if(a[(i+j)%m]==item)
		{
			printf("%d %d\n",(i+j)%m,item);
			flag=1;
			break;
		}
	}
	if(flag==0)
		printf("-1\n");
}
int main()
{
	int i,n,m,item,sk,ik;
	int *a;
	char f;
	scanf("%d %d",&m,&n);
	a=(int *)malloc(sizeof(int)*m);
	for(i=0;i<m;i++)
	{
		a[i]=0;
	}
	while (1)
	{
		scanf(" %c", &f);
		if (f == 'i')
		{
			scanf("%d", &item);
			ik=insert(a,m,n,item);
			printf("%d\n",ik);
		}
		else if (f == 's')
		{
			scanf("%d", &item);
			search(a,m,n,item);
		}
		else
			break;
	}
	free(a);
}