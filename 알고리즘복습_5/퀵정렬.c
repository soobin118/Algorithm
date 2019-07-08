#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int* Partition(int *a, int l, int r, int k)
{
	int i, j, temp;
	int p[2];
	return p;
}
void inPlaceQuickSort(int *a, int l, int r)
{
	int pivot[2];
	srand(time(NULL));
	int k = rand() % (r - l + 1) + 1;
	*pivot = Partition(a, l, r,k);
	inPlaceQuickSort(a, l, pivot[0]);
	inPlaceQuickSort(a, pivot[1], r);
}
int main()
{
	int n;
	int *arr;
	scanf("%d", &n);
	arr = (int *)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	inPlaceQuickSort(arr, 0, n-1);
	free(arr);
	return 0;
}