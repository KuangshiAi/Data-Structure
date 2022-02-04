#include<stdio.h>
#include<stack>
#include<ctype.h>
#include<string.h>
#include"genlist.h"
#define maxsize 50
int i = 0;
int j=0;
GenListNode *p[maxsize];
char name[maxsize];
int search(char*name,char str)
{
	for (int k = 0; k < j; k++)
	{
		if (name[k] == str)
			return k+1;
	}
	return 0;
}
void createlist(char *str,GenListNode *&ls)
{
	if (isupper(str[i]))//如果遇到了大写字母，说明是表头
	{
		ls = new GenListNode;
		ls->utype = 2;
		if (search(name, str[i]))//用于判断当前大写字母是否已经是子表
		{
			GenListNode* q = p[search(name, str[i])-1];
			q->info.hlink->info.ref++;//若是，则引用加一
			ls->info.hlink = q;
			i++;//默认出现过的子表再次出现不会显示其内容
			createlist(str, ls);//这一步是因为此时该大写字母相当于一个元素
		}
		else
		{
			name[j++] = str[i];
			p[j - 1] = ls;
			ls->info.hlink = new GenListNode;
			ls->info.hlink->utype = 0;
			ls->info.hlink->info.ref = 1;
			i += 2;
			createlist(str, ls->info.hlink->tlink);//先递归深入下层子表
			createlist(str, ls);//再递归完成当前深度表的建立
		}
	}
	else if (isalnum(str[i]))//如果是小写字母或者数字，则是原子
	{
		ls = new GenListNode;
		ls->utype = 1;
		ls->info.value = str[i];
		i++;
		createlist(str, ls);//递归到ls是因为下一步做什么取决于后括号是否结束
	}
	else if (str[i] == ',')
	{
		i++;
		createlist(str, ls->tlink);//说明当前层的表元未录入完全
	}
	else if (str[i] = ')')
		ls->tlink = NULL;
}//未想到如何通过输出来检验程序的正确性，麻烦TA阅读一下代码啦
int main()
{
	printf("请输入广义表的字符串表示\n");
	char str[100];
	scanf_s("%s", str, 100);
	GenListNode* ls;
	createlist(str, ls);
	return 0;
}