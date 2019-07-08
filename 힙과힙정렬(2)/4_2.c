#include<stdio.h>
int h[100];//H 힙
int n = 0;//힙의 크기
void downHeap(int i)
{
	int t;
	if ((i * 2)>n && (i * 2 + 1) > n)//외부노드면 반환
		return 0;
	else if((i*2+1)<=n)
	{
		if (h[i]<h[i * 2] || h[i]<h[i * 2 + 1])
		{
			if (h[i * 2]>h[i * 2 + 1])//왼쪽자식과 오른쪽자식중 더 큰것으로 바꾸기
			{
				t = h[i];
				h[i] = h[i * 2];
				h[i * 2] = t;
				downHeap(i * 2);
			}
			else
			{
				t = h[i];
				h[i] = h[i * 2 + 1];
				h[i * 2 + 1] = t;
				downHeap(i * 2 + 1);
			}
		}
	}
	else
	{
		if (h[i] < h[i * 2])
		{
			t = h[i];
			h[i] = h[i * 2];
			h[i * 2] = t;
			downHeap(i * 2);
		}
	}
}
void buildHeap(int i)
{
	for (i = n / 2; i >= 1; i--)
	{
		downHeap(i);
	}
}
void printArray()
{
	int i;
	for (i = 1; i <= n; i++)
	{
		printf(" %d", h[i]);
	}
	printf("\n");
}
void inPlaceHeapSort()
{
	int i,temp,size;
	size = n;
	for (i = size; i > 1; i--)
	{
		temp = h[1];
		h[1] = h[i];
		h[i] = temp;
		n--;
		downHeap(1);
	}
	n = size;
}
int main()
{
	int i;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		scanf("%d", &h[i]);
	}
	buildHeap(1);
	inPlaceHeapSort();
	printArray();
}