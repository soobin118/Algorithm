#include<stdio.h>
#include<stdlib.h>

void inPlaceInsertSort(int *a, int size)
{
	int temp,i,j;
	for (i = 1; i < size; i++)
	{
		int k = i;
		for (j = i-1; j >= 0; j--)
		{
			if (a[j] > a[k])
			{
				temp = a[j];
				a[j] = a[k];
				a[k] = temp;
				k = j;
			}
		}
	}
}

void print(int *a, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf(" %d", a[i]);
	}
	printf("\n");
}

int main()
{
	int n;	// size of array
	int *arr;
	scanf("%d", &n);
	arr = (int *)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	inPlaceInsertSort(arr, n);
	print(arr, n);
	free(arr);
	return 0;
}