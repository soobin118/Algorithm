#include<stdio.h>

int heap[100];	// heap array
int n = 0;		// current size of heap

void upHeap(int id) {
	if (id == 1)
		return;
	int pid = id / 2;	// pid = parent index
	if (heap[pid] < heap[id])
	{
		int temp = heap[pid];
		heap[pid] = heap[id];
		heap[id] = temp;
	}
	upHeap(pid);
}

void downHeap(int id) {
	int left = id * 2;			// left child index
	int right = id * 2 + 1;		// right child index
	if (left > n)
		return;
	else if (left == n )
	{
		if (heap[id] < heap[left])
		{
			int temp = heap[id];
			heap[id] = heap[left];
			heap[left] = temp;
		}
		return;
	}
	else {
		if (heap[left] > heap[right])
		{
			if (heap[id] < heap[left])
			{
				int temp = heap[id];
				heap[id] = heap[left];
				heap[left] = temp;
				downHeap(left);
			}
		}
		else
		{
			if (heap[id] < heap[right])
			{
				int temp = heap[id];
				heap[id] = heap[right];
				heap[right] = temp;
				downHeap(right);
			}
		}
	}
}

void insertKey(int k) {
	n++;
	heap[n] = k;
	upHeap(n);
	printf("0\n");
}

int removeMax() {
	int temp;
	temp = heap[1];
	heap[1] = heap[n--];
	downHeap(1);
	return temp;
}

void printHeap() {
	for (int i = 1; i <= n; i++)
		printf(" %d", heap[i]);
	printf("\n");
}

int main()
{
	char op;	// operation
	int key;
	while (1)
	{
		scanf("%c", &op);
		switch (op)
		{
		case 'i':	// insert the key to heap and print zero
			scanf("%d", &key);
			insertKey(key);
			break;
		case 'd':	// delete the key of root from heap
			key = removeMax();
			printf("%d\n", key);
			break;
		case 'p':	// print the element of heap
			printHeap();
			break;
		case 'q':	// quit the program
			exit(1);
		default:
			break;
		}
		getchar();
	}
	return 0;
}