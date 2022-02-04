#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//采用与快排中partition相似的左右指针法
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
			if (a[left] + a[right] > a[i])//a[i]是三角形中最长的一条边
			{
				count += (right - left);//左指针到右指针之间的所有元素都满足构成三角形
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