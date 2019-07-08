#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int inPlacePartition(int *a, int l,int r)
{
	int temp,i,j,pivot;
	int pi,p[3],pmin,pmax;
	srand(time(NULL));
	for(i=0;i<3;i++)
	{
		p[i]=rand()%(r-l+1)+l;
			for(j=0;j<i;j++)
			{
				if(p[j]==p[i])
				{
					p[i]=rand()%(r-l+1)+l;
					j--;
				}
			}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<2;j++)
		{
			if(a[p[j]]>a[p[j+1]])
			{
				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
		}
	}
	pi=p[1];
	pivot=a[pi];
	temp=a[pi];
	a[pi]=a[r];
	a[r]=temp;
	i=l;
	j=r-1;
	while(i<=j)
	{
		while(i<=j && a[i]<=pivot)
			i=i+1;
		while(j>=i && a[j]>=pivot)
			j=j-1;
		if(i<j)
		{
			temp=a[i];
			a[i]=a[j];
			a[j]=temp;
		}
	}
	temp=a[i];
	a[i]=a[r];
	a[r]=temp;
	return i;
}
void inPlaceQuickSort(int *a,int l,int r)
{
	int index;
	if(l>=r)
		return;
	index=inPlacePartition(a,l,r);
	inPlaceQuickSort(a,l,index-1);
	inPlaceQuickSort(a,index+1,r);
}

int main()
{
	int i,n,*a;
	scanf("%d",&n);
	a=(int *)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
		scanf("%d",a+i);
	inPlaceQuickSort(a,0,n-1);
	for(i=0;i<n;i++)
	{
		printf(" %d",a[i]);
	}
	printf("\n");
}