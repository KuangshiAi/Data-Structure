#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//�����������partition���Ƶ�����ָ�뷨
int triangle(vector<int>a)
{
	int count = 0;
	int n = a.size();
	sort(a.begin(), a.end());
	for (int i = 0; i < n; i++)
	{
		int left = 0;
		int right = i - 1;
		while (left < right)
		{
			if (a[left] + a[right] > a[i])//a[i]�������������һ����
			{
				count += (right - left);//��ָ�뵽��ָ��֮�������Ԫ�ض����㹹��������
				right--;
			}
			else
			{
				left++;
			}
		}
	}
	return count;
}
int main()
{
	vector<int> a = { 4,2,3,2 };
	printf("%d\n", triangle(a));
	return 0;
}