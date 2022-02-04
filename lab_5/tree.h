#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
using namespace std;
typedef struct tree
{
	char data;
	struct tree* leftchild, * rightchild;
}Tree;
bool createTree(Tree*&p)
{
	char temp;
	cout<<"先序输入字符"<<endl;
	cin >> temp;
	if (temp == '#')
	{
		p = NULL;
	}
	else
	{
		if (!(p = new Tree))
			return false;
		p->data = temp;
		createTree(p->leftchild);
		createTree(p->rightchild);
	}
	return true;
}
void preorder(Tree* p)
{
	if (p != NULL)
	{
		cout << p->data;
		preorder(p->leftchild);
		preorder(p->rightchild);
	}
}
void inorder(Tree* p)
{
	if (p != NULL)
	{
		inorder(p->leftchild);
		cout << p->data;
		inorder(p->rightchild);
	}
}
bool reverse(Tree*& p)
{//使用递归的方法
	if (p == NULL)
		return true;
	reverse(p->leftchild);
	reverse(p->rightchild);
	Tree* temp;
	temp = p->leftchild;
	p->leftchild = p->rightchild;
	p->rightchild = temp;
}
