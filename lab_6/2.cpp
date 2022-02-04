#include<stdio.h>
#include"heap.h"
void frequency(int* num, int k,int n)
{
	int fre[10] = { 0 };
	for (int i = 0; i < n; i++)
	{
		fre[num[i]]++;
	}
	MinHeap<int> a(k);//����һ��Ԫ�ظ���Ϊk����С��
	int i = 0;
	while (a.Insert(fre[i]))
		i++;
	int x;
	while (i < 10)
	{
		if (fre[i] > a.heap[0])//���Ƶ�ʴ��ڵ�ǰ������СԪ������ѣ���������
		{
			a.Remove(x);
			a.Insert(fre[i]);
		}
		i++;
	}
	printf("����Ƶ��ǰ%d�ߵ�Ԫ����",k);
	for (i = 0; i < k; i++)
	{
		a.Remove(x);
		for (int j = 0; j < 10; j++)
		{
			if (fre[j] == x)
				printf("%d ",j);
		}
	}
}
int main()
{
	int num[] = { 1,1,1,2,2,3 };
	frequency(num, 1, 6);
	return 0;
}