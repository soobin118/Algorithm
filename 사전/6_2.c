#include<stdio.h>
#include<stdlib.h>
void find(int *a,int k,int l,int r,int *mp,int n)
{
	int flag=0,temp;
	while(1)
	{
		if(l>r)
		{
			if(flag==0)
				*mp=n;
			else
				*mp=temp;
			break;
		}
		if(a[(l+r)/2]==k)
		{
			*mp=(l+r)/2;
			break;
		}
		if(a[(l+r)/2]>k)
		{
			temp=(l+r)/2;
			r=(l+r)/2-1;
			flag=1;
		}
		else if(a[(l+r)/2]<k)
		{
			l=(l+r)/2+1;
		}
	}
}
int main()
{
	int n,i,k,min=0,*mp=&min;
	int *a;
	scanf("%d",&n);
	scanf("%d",&k);
	a=(int *)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	{
		scanf("%d",a+i);
	}
	find(a,k,0,n-1,mp,n);
	printf(" %d\n",*mp);
	free(a);
}