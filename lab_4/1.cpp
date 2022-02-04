#include<stdio.h>
int length;
void swap(int* a, int p, int q)
{
	int temp = a[p];
	a[p] = a[q];
	a[q] = temp;
}
void permute(int* a, int p, int q)
{
	if (p == q)
	{
		printf("[");
		for (int j = 0; j < length; j++)
		{
			printf("%d", a[j]);
			if (j < length - 1)
				printf(",");
		}
		printf("]");
	}
	else
	{
		for (int i = p; i < length; i++)
		{
			swap(a, i, p);
			permute(a, p + 1, q);
			swap(a, i, p);
		}
	}
}
int main()
{
	int a[] = { 1,8,9 };
	length = sizeof(a) / sizeof(a[0]);
	printf("[");
	permute(a, 0, length - 1);
	printf("]");
	return 0;
}