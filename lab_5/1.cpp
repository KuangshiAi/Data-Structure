#include"tree.h"
#include<queue>
bool reverse2(Tree*&T)
{//���÷ǵݹ�ķ���ʵ�֣��ݹ鷨���tree.h
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
	cout << "������������� "<< endl;
	cout << "ǰ���������" << endl;
	preorder(T);
	cout<<endl;
	cout << "�����������" << endl;
	inorder(T);
	cout << endl;
	reverse(T);
	cout << "��ת��ǰ���������"<<endl;
	preorder(T);
	cout << endl;
	cout << "��ת�������������" << endl;
	inorder(T);
	return 0;
}