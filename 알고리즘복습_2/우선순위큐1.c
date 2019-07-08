#include<stdio.h>
#include<stdlib.h>

void inPlaceSelectSort(int *a,int size)
{
	int maxvalue, maxindex;

	for (int i = 0; i < size-1; i++)
	{
		maxvalue = a[0];
		maxindex = 0;
		for (int j = 0; j < size-i; j++)
		{
			if (maxvalue < a[j])
			{
				maxvalue = a[j];
				maxindex = j;
			}
		}
		int temp;
		temp = a[size - i-1];
		a[size - i - 1] = a[maxindex];
		a[maxindex] = temp;
	}
}
void print(int *a,int size)
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
	int *arr; // array
	scanf("%d", &n);
	arr = (int *)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	inPlaceSelectSort(arr,n);
	print(arr,n);
	free(arr);
	return 0;
}