#include<stdio.h>
int h[100]={0};//힙배열
int n=0;// 힙의 크기
void downHeap(int i)
{
	int t;
	if(h[i*2]==0 && h[i*2+1]==0)//외부노드면 반환
		return 0;
	else
	{
		if(h[i]<h[i*2] || h[i]<h[i*2+1])
		{
			if(h[i*2]>h[i*2+1])//왼쪽자식과 오른쪽자식중 더 큰것으로 바꾸기
			{
				t=h[i];
				h[i]=h[i*2];
				h[i*2]=t;
				downHeap(i*2);
			}
			else
			{
				t=h[i];
				h[i]=h[i*2+1];
				h[i*2+1]=t;
				downHeap(i*2+1);
			}
		}
	}
}
void printHeap()
{
	int i;
	for(i=1;i<=n;i++)
	{
		printf(" %d",h[i]);
	}
	printf("\n");
}
void buildHeap(int i)
{
	for(i=n/2;i>=1;i--)
	{
		downHeap(i);
	}
}
int main()
{
	int cnt,i;
	scanf("%d",&cnt);
	for(i=0;i<cnt;i++)
	{
		n+=1;
		scanf("%d", &h[n]);
	}
	buildHeap(1);
	printHeap();
}