#include<stdio.h>
int h[100];//H ��
int n=0;//���� ũ��
void upHeap(int i)
{
	int temp;
	if(i==1)//��Ʈ�� ��ȯ
		return 0;
	else{
	if(i%2==0)//�������ڽ��϶�
	{
		if(h[i]>h[i/2])
		{
			temp=h[i];
			h[i]=h[i/2];
			h[i/2]=temp;
		}
		upHeap(i/2);
	}
	else//�����ڽ��϶�
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
	if(h[i*2]==0 && h[i*2+1]==0)//�ܺγ��� ��ȯ
		return 0;
	else
	{
		if(h[i]<h[i*2] || h[i]<h[i*2+1])
		{
			if(h[i*2]>h[i*2+1])//�����ڽİ� �������ڽ��� �� ū������ �ٲٱ�
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
void insertItem(int key)//����
{
	n+=1;
	h[n]=key;
	upHeap(n);
	printf("0\n");
}
int removeMax()//�ִ밪�����
{
	int key=h[1];
	h[1]=h[n];//��������� ��Ʈ�� �ֱ�
	h[n]=0;//��������� �����
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