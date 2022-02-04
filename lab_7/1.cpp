#include<stdio.h>
void searchpos(int* nums, int target,int len)//这是一个时间复杂度为O(n)的方法
{
	if (target > nums[len - 1] || target < nums[0])
	{
		printf("[-1,-1]\n");
		return;
	}
	int low = 0;
	int high = len - 1;
	int mid = (high +low) / 2;
	while (low <= high)
	{
		if (target < nums[mid])
			high = mid - 1;
		else if (target > nums[mid])
			low = mid + 1;
		else
			break;
		mid = (high + low) / 2;
	}
	if (low <= high)
	{
		int begin, end;
		int i;
		for (i = mid; nums[i] == target && i; i--);
		begin = i+1;
		for (i = mid; nums[i] == target && i < len; i++);
		end = i-1;
		printf("[%d,%d]\n", begin, end);
	}
	else
	{
		printf("[-1,-1]\n");
	}
}
void searchpos2(int* nums, int target, int len)//这是时间复杂度O(log n)的方法
{
	if (target > nums[len - 1] || target < nums[0])
	{
		printf("[-1,-1]\n");
		return;
	}
	int max, min;
	int low = 0;
	int high = len - 1;
	int mid;
	if (target == nums[len - 1])
		max = len;
	else
	{
		while (low!=high)//从左向右找出第一个大于target的元素
		{
			mid = (low+high) / 2;
			if (target < nums[mid])
				high = mid;
			else
				low = mid + 1;
		}
		max = low;
	}
	if (target == nums[0])
		min = -1;
	else
	{
		low = 0;
		high = len - 1;
		while (low!=high)//从右向左找出第一个小于target的元素
		{
			mid = (low+high )/ 2;
			if (target > nums[mid])
				low=mid;
			else
				high = mid-1 ;
		}
		min = low;
	}
	if (max - min == 1)
		printf("[-1,-1]\n");
	else
		printf("[%d,%d]\n", min+1, max-1);
}
int main()
{
	int nums[] = {5,7,7,8,8,8,8,8,8,8,10};
	int len = sizeof(nums) / sizeof(int);
	int target = 8;
	searchpos2(nums, target,len);
	return 0;
}