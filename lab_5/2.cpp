#include"tree.h"
#include<string.h>
#define maxsize 100
bool check(Tree*& p, Tree*& q)
{
	if (p == NULL && q == NULL)
		return true;
	if (p == NULL || q == NULL)
		return false;
	if (p->data != q->data)
		return false;
	else
		return check(p->leftchild, q->rightchild) && check(p->rightchild, q->leftchild);
}
bool isSymmetry(Tree*&root)
{
	if (root == NULL)
		return true;
	return check(root->leftchild, root->rightchild);
}
//实现方法二：判断翻转以后二叉树的前序遍历和中序遍历是否都没有改变
char pre1[maxsize] = { 0 };
char in1[maxsize] = { 0 };
char pre2[maxsize] = { 0 };
char in2[maxsize] = { 0 };
int i = 0;
void preorderplus(Tree* p,char*pre)
{
	if (p != NULL)
	{
		pre[i++] = p->data;
		preorderplus(p->leftchild,pre);
		preorderplus(p->rightchild,pre);
	}
	i = 0;
}
void inorderplus(Tree* p,char*in)
{
	if (p != NULL)
	{
		inorderplus(p->leftchild,in);
		in[i++] = p->data;
		inorderplus(p->rightchild,in);
	}
	i = 0;
}
bool isSymmetry2(Tree*& root)
{
	preorderplus(root, pre1);
	inorderplus(root, in1);
	reverse(root);
	preorderplus(root, pre2);
	inorderplus(root, in2);
	if (!(strcmp(pre1, pre2)) && !(strcmp(in1, in2)))
		return true;
	else
		return false;
}
int main()
{
	Tree* T;
	createTree(T);
	cout << "二叉树构造完成" << endl;
	cout << "前序遍历如下" << endl;
	preorder(T);
	cout << endl;
	cout << "中序遍历如下" << endl;
	inorder(T);
	cout << endl;
	if (isSymmetry(T))
		cout << "方法一判断该二叉树镜面对称" << endl;
	else
		cout << "方法一判断该二叉树非镜面对称" << endl;
	if (isSymmetry2(T))
		cout << "方法二判断该二叉树镜面对称" << endl;
	else
		cout << "方法二判断该二叉树非镜面对称" << endl;
	return 0;
}