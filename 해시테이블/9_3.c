#include<stdio.h>
#include<stdlib.h>
int funch(int key, int m)
{
	return key%m;
}
int funch2(int key, int q) {
	return q - (key%q);
}
void insert(int key,int *hash,int m,int q) {
	int fi,i=1;
	if (hash[funch(key, m)] == 0)
	{
		hash[funch(key, m)] = key;
		printf("%d\n", funch(key, m));
		return;
	}
	else
	{
		fi = funch2(key, q);
		while (1)
		{
			printf("C");
			if (hash[(funch(key, m) + (i*fi)) % m] == 0)
			{
				hash[(funch(key, m) + (i*fi)) % m] = key;
				printf("%d\n", (funch(key, m) + (i*fi)) % m);
				return;
			}
			else
				i++;
		}
	}
}
void search(int key,int *hash,int m) {
	int i=0;
	for (i = 0; i < m;i++)
	{
		if (hash[i] == key)
		{
			printf("%d %d\n", i, key);
			return;
		}
	}
	printf("-1\n");
}
void print(int *hash, int m) {
	int i=0;
	for (i = 0; i < m;i++)
	{
		printf(" %d", hash[i]);
	}
	printf("\n");
}
int main()
{
	int i, m, n, q;
	int *hash;
	char c;
	int key;
	scanf("%d%d%d", &m, &n, &q);
	hash = (int *)malloc(sizeof(int)*m);
	for (i = 0; i < m; i++)
	{
		hash[i] = 0;
	}
	while (1) {
		scanf(" %c", &c);
		if (c == 'i') {
			scanf("%d", &key);
			insert(key,hash,m,q);
		}
		else if (c == 's')
		{
			scanf("%d", &key);
			search(key,hash,m);
		}
		else if (c == 'p')
		{
			print(hash,m);
		}
		else
		{
			print(hash,m);
			break;
		}
	}
	free(hash);
}