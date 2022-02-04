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
	printf("请输入规模n\n");
	int n;
	scanf_s("%d", &n);
	printf("由%d个节点组成的互不相同的二叉搜索树有%d种", n, Binnums(n));
}