#include"tree.h"
#include<queue>
bool reverse2(Tree*&T)
{//采用非递归的方法实现，递归法详见tree.h
	if (T == NULL)
		return true;
	queue<Tree*> que;
	que.push(T);
	if (!que.empty())
	{
		Tree* temp = que.front();
		if (temp->leftchild != NULL)
			que.push(temp->leftchild);
		if(temp->rightchild!=NULL)
			que.push(temp->rightchild);
		Tree* temp2;
		temp2 = temp->leftchild;
		temp->leftchild = temp->rightchild;
		temp->rightchild = temp2;
		que.pop();
	}
}
int main()
{
	Tree* T;
	createTree(T);
	cout << "二叉树构造完成 "<< endl;
	cout << "前序遍历如下" << endl;
	preorder(T);
	cout<<endl;
	cout << "中序遍历如下" << endl;
	inorder(T);
	cout << endl;
	reverse(T);
	cout << "翻转后前序遍历如下"<<endl;
	preorder(T);
	cout << endl;
	cout << "翻转后中序遍历如下" << endl;
	inorder(T);
	return 0;
}