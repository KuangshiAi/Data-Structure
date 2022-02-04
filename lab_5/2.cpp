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
//ʵ�ַ��������жϷ�ת�Ժ��������ǰ���������������Ƿ�û�иı�
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
	cout << "�������������" << endl;
	cout << "ǰ���������" << endl;
	preorder(T);
	cout << endl;
	cout << "�����������" << endl;
	inorder(T);
	cout << endl;
	if (isSymmetry(T))
		cout << "����һ�жϸö���������Գ�" << endl;
	else
		cout << "����һ�жϸö������Ǿ���Գ�" << endl;
	if (isSymmetry2(T))
		cout << "�������жϸö���������Գ�" << endl;
	else
		cout << "�������жϸö������Ǿ���Գ�" << endl;
	return 0;
}