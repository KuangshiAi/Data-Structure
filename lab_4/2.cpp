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
	if (isupper(str[i]))//��������˴�д��ĸ��˵���Ǳ�ͷ
	{
		ls = new GenListNode;
		ls->utype = 2;
		if (search(name, str[i]))//�����жϵ�ǰ��д��ĸ�Ƿ��Ѿ����ӱ�
		{
			GenListNode* q = p[search(name, str[i])-1];
			q->info.hlink->info.ref++;//���ǣ������ü�һ
			ls->info.hlink = q;
			i++;//Ĭ�ϳ��ֹ����ӱ��ٴγ��ֲ�����ʾ������
			createlist(str, ls);//��һ������Ϊ��ʱ�ô�д��ĸ�൱��һ��Ԫ��
		}
		else
		{
			name[j++] = str[i];
			p[j - 1] = ls;
			ls->info.hlink = new GenListNode;
			ls->info.hlink->utype = 0;
			ls->info.hlink->info.ref = 1;
			i += 2;
			createlist(str, ls->info.hlink->tlink);//�ȵݹ������²��ӱ�
			createlist(str, ls);//�ٵݹ���ɵ�ǰ��ȱ�Ľ���
		}
	}
	else if (isalnum(str[i]))//�����Сд��ĸ�������֣�����ԭ��
	{
		ls = new GenListNode;
		ls->utype = 1;
		ls->info.value = str[i];
		i++;
		createlist(str, ls);//�ݹ鵽ls����Ϊ��һ����ʲôȡ���ں������Ƿ����
	}
	else if (str[i] == ',')
	{
		i++;
		createlist(str, ls->tlink);//˵����ǰ��ı�Ԫδ¼����ȫ
	}
	else if (str[i] = ')')
		ls->tlink = NULL;
}//δ�뵽���ͨ�����������������ȷ�ԣ��鷳TA�Ķ�һ�´�����
int main()
{
	printf("������������ַ�����ʾ\n");
	char str[100];
	scanf_s("%s", str, 100);
	GenListNode* ls;
	createlist(str, ls);
	return 0;
}