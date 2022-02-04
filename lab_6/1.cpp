#include<stdio.h>
#include"tree.h"
int tag = 0;
void minpath(Tree *root,int sum,int& min)
{
	if (root != NULL)
	{
		if (root->rightchild == NULL && root->leftchild == NULL)
		{
			sum = sum + root->data;
			if (tag == 0)
				min = sum;
			tag = 1;
			if (sum < min)
				min = sum;
			sum = 0;
			return;
		}
		else 
		{
			sum = sum + root->data;
			minpath(root->leftchild,sum, min);
			minpath(root->rightchild,sum, min);
		}
	}
}
int main()
{
	Tree* root = NULL;
	createTree(root);
	int min=0;
	int sum = 0;
	minpath(root, sum,min);
	printf("所有路径中和最小的路径和是%d", min);
	return 0;
}