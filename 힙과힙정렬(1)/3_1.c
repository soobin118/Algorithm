#include<stdio.h>
int h[100];//H 힙
int n=0;//힙의 크기
void upHeap(int i)
{
	int temp;
	if(i==1)//루트면 반환
		return 0;
	else{
	if(i%2==0)//오른쪽자식일때
	{
		if(h[i]>h[i/2])
		{
			temp=h[i];
			h[i]=h[i/2];
			h[i/2]=temp;
		}
		upHeap(i/2);
	}
	else//왼쪽자식일때
	{
		if(h[i]>h[(i-1)/2])
		{
			temp=h[i];
			h[i]=h[(i-1)/2];
			h[(i-1)/2]=temp;
		}
		upHeap((i-1)/2);
	}
	}
}
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
void insertItem(int key)//삽입
{
	n+=1;
	h[n]=key;
	upHeap(n);
	printf("0\n");
}
int removeMax()//최대값지우기
{
	int key=h[1];
	h[1]=h[n];//마지막노드 루트로 넣기
	h[n]=0;//마지막노드 지우기
	n-=1;
	downHeap(1);
	return key;
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
int main()
{
	char c;
	int key,r;
	while(1)
	{
		scanf(" %c",&c);
		if(c=='i')
		{
			scanf("%d",&key);
			insertItem(key);
		}
		else if(c=='d')
		{
			r=removeMax();
			printf("%d\n",r);
		}
		else if(c=='p')
		{
			printHeap();
		}
		else
			break;
	}
}