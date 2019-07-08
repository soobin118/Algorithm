#include<stdio.h>
#include<stdlib.h>
void find(int *a,int k,int l,int r,int *mp,int flag)
{
	if(l>r)
	{
		if(flag==0)
			*mp=-1;
		return;
	}
	if(k>=a[(l+r)/2])
	{
		if(a[*mp]<a[(l+r)/2])
		{
			*mp=(l+r)/2;//x<=k를 만족할경우
		}
		flag=1;
	}
	if(k>a[(l+r)/2])
		find(a,k,(l+r)/2+1,r,mp,flag);//key값이 중간값보다 클경우
	else
		find(a,k,0,(l+r)/2-1,mp,flag);//key값이 중간값보다 작을경우
}
int main()
{
	int n,i,k,max=0,*mp=&max,flag=0;
	int *a;
	scanf("%d",&n);
	scanf("%d",&k);
	a=(int *)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	{
		scanf("%d",a+i);
	}
	find(a,k,0,n-1,mp,flag);
	printf(" %d\n",*mp);
	free(a);
}