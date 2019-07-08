#include<stdio.h>
#include<stdlib.h>
void selectinplace(int *ar,int n,int cnt)
{
	int max,i,index=0,temp;
	max = *ar;
	for (i = 0; i < cnt+1; i++)
	{
		if (max < *(ar + i))
		{
			max = *(ar + i);
			index = i;
		}
	}
	temp = *(ar + index);
	*(ar + index) = *(ar + cnt);
	*(ar + cnt) = temp;
}
int main()
{
	int n,*ar,i;
	scanf("%d", &n);
	ar = (int *)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", ar + i);
	}
	for (i = 0; i < n; i++)
	{
		selectinplace(ar, n, n-1-i);
	}
	for (i = 0; i < n; i++)
		printf(" %d", *(ar + i));
	free(ar);
}