#include<stdio.h>
#include<stdlib.h>
void inplace(int *a,int n,int cnt)
{
	int i,temp,index,flag=0;
	for (i = 0; i < cnt; i++)
	{
		if (a[cnt] < a[i])
		{
			flag = 1;
			break;
		}
	}
	if (flag == 1)
	{
		index = i;
		temp = a[cnt];
		for (i = cnt - 1; i >= index; i--)
		{
			a[i + 1] = a[i];
		}
		a[index] = temp;
	}
}

int main()
{
	int n,*a,i;
	scanf("%d", &n);
	a = (int *)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", a + i);
	}
	for (i = 1; i < n; i++)
	{
		inplace(a, n, i);
	}
	for (i = 0; i < n; i++)
	{
		printf(" %d", a[i]);
	}
	printf("\n");
	free(a);
}