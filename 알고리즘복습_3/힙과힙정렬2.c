#include<stdio.h>

int h[100];	// heap array
int n = 0;		// size of heap

void downHeap(int id) {
	int left = id * 2;			// left child index
	int right = id * 2 + 1;		// right child index
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
	else {
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
		else
		{
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

void rBuildHeap(int id)
{
	if (id > n)
		return;
	rBuildHeap(id * 2);
	rBuildHeap(id * 2 + 1);
	downHeap(id);
	return;
}

void buildHeap()
{
	for (int i = n / 2; i > -1; i--)
	{
		downHeap(i);
	}
	return;
}

void printHeap() {
	for (int i = 1; i <= n; i++)
		printf(" %d", h[i]);
	printf("\n");
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
	printHeap();
	return 0;
}