#include<stdio.h>
#include<stdlib.h>
int quickSort(int *a,int l,int r)
{
	int temp,i,j,pivot,pi;
	if(l>=r)
		return;
	pivot=a[(l+r)/2];
	pi=(l+r)/2;
	temp=a[r];
	a[r]=a[pi];
	a[pi]=temp;
	i=l;
	j=r-1;
	while(i<=j)
	{
		while(i<=j && a[i]<=pivot)
		{
			i++;
		}
		while(i<=j && a[j]>=pivot)
		{
			j--;
		}
		if(i<j)
		{
			temp=a[i];
			a[i]=a[j];
			a[j]=temp;
		}
	}
	temp=a[r];
	a[r]=a[i];
	a[i]=temp;
	return i;
}
void rquickSort(int *a, int l, int r)
{
	int index;
	if(l>r)
		return;
	index=quickSort(a, l,r);
	rquickSort(a,l,index-1);
	rquickSort(a,index+1,r);
}
int main()
{
	int n,i;
	int *a;
	scanf("%d",&n);
	a=(int *)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	{
		scanf("%d",a+i);
	}
	rquickSort(a,0,n-1);
	for(i=0;i<n;i++)
	{
		printf(" %d",a[i]);
	}
	printf("\n");
	
	free(a);
}