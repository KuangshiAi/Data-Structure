#include"tree.h"
#include<stdio.h>
int height(Tree* root)
{
	if (root == NULL)
		return 0;
	int left = height(root->leftchild);
	if (left == -1)
		return -1;
	int right = height(root->rightchild);
	if (right == -1)
		return -1;
	if (right - left<2 && right - left>-2)
		return left > right ? left : right + 1;
	else
		return -1;
}
bool isbalanced(Tree* root)
{
	return height(root) != -1;
}
int main()
{
	Tree* root;
	createTree(root);
	printf("二叉树创建完成\n");
	if (isbalanced(root))
		printf("true\n");
	else
		printf("false\n");
	return 0;
}