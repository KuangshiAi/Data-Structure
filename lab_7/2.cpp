#include<stdio.h>
int Binnums(int n)
{
	int* G = new int(n + 1);
	G[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		G[i] = 0;
		for (int j = 0; j < i; j++)
		{
			G[i] += G[j] * G[i - j-1];
		}
	}
	return G[n];
}
int main()
{
	printf("�������ģn\n");
	int n;
	scanf_s("%d", &n);
	printf("��%d���ڵ���ɵĻ�����ͬ�Ķ�����������%d��", n, Binnums(n));
}