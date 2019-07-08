#include<stdio.h>

int h[100];	// heap
int n;		// the size of heap

void printArray()
{
	for (int i = 1; i <= n; i++)
		printf(" %d", h[i]);
	printf("\n");
}
void downHeap(int id)
{
	int left = id * 2;
	int right = id * 2 + 1;
	if (left > n)
		return;
	else if (left == n)
	{
		if (h[id] < h[left])
		{
			int temp = h[id];
			h[id] = h[left];
			h[left] = temp;
		}
		return;
	}
	else
	{
		if (h[left] > h[right])
		{
			if (h[id] < h[left])
			{
				int temp = h[id];
				h[id] = h[left];
				h[left] = temp;
				downHeap(left);
			}
		}
		else {
			if (h[id] < h[right])
			{
				int temp = h[id];
				h[id] = h[right];
				h[right] = temp;
				downHeap(right);
			}
		}
	}
}
void upHeap(int id)
{
	if (id <= 1)
		return;
	int pid = id / 2;
	if (h[id] > h[pid])
	{
		int temp = h[id];
		h[id] = h[pid];
		h[pid] = temp;
		upHeap(pid);
	}
}
void insertItem(int key)
{
	n++;
	h[n] = key;
	upHeap(n);
}
void rBuildHeap(int id)
{
	if (id > n)
		return;
	rBuildHeap(2 * id);
	rBuildHeap(2 * id + 1);
	downHeap(id);
	return;
}
void buildHeap()
{
	for (int i = n / 2; i >= 1; i--)
		downHeap(i);
	return;
}

void inPlaceHeapSort()
{
	int tmp;
	int pn = n;
	for (int i = n; i > 1; i--)
	{
		tmp = h[1];
		h[1] = h[i];
		h[i] = tmp;
		n--;
		downHeap(1);
	}
	n = pn;
}
int main()
{
	int cnt;
	scanf("%d", &cnt);
	for (int i = 1; i <= cnt; i++)
	{
		scanf("%d", &h[i]);
		n++;
	}
	rBuildHeap(1);
	inPlaceHeapSort();
	printArray();
	return 0;
}