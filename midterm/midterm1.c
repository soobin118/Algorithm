#include<stdio.h>
#include<stdlib.h>
void upHeap(int *a,int i)
{
	int temp;
	if(i<=1)
		return;
	if(i%2==0)
	{
		if(a[i]>a[i/2])
		{
			temp=a[i];
			a[i]=a[i/2];
			a[i/2]=temp;
			upHeap(a,i/2);
		}
	}
	else
	{
	if(a[i]>a[(i-1)/2])
	{
		temp=a[i];
		a[i]=a[(i-1)/2];
		a[(i-1)/2]=temp;
		upHeap(a,(i-1)/2);
	}
	}
}
void insertItem(int *a, int index,int k)
{
	a[index]=k;
	upHeap(a,index);
}
int main()
{
	int i,n,*a,k;
	scanf("%d",&n);
	a=(int *)malloc(sizeof(int)*(n+1));
	for(i=1;i<=n;i++)
	{
		scanf("%d",&k);
		insertItem(a,i,k);
	}
	for(i=1;i<=n;i++)
	{
		printf(" %d",a[i]);
	}
	free(a);
}