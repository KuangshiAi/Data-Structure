#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxsize 100
int judge(char* str)
{
	int length;
	int i = 0;
	while (str[i])
		i++;
	length = i;
	for (i = 0; i < length; i++)
	{
		if (str[i] != str[length - 1 - i])
			length = 0;
	}
	return length;
}
char* substring(char* str, int position, int len)//position starts from 0
{
	char* result = (char*)calloc(len + 1,sizeof(char));
	for (int i = 0; i < len; i++)
		result[i] = str[position + i];
	return result;
}
int main()
{
	char str[maxsize];
	printf("请输入待检测字符串\n");
	scanf_s("%s", str, maxsize);
	int len = strlen(str);
	int maxlength=0;
	int i, j;
	char* maxstr=NULL;
	for(i=1;i<=len;i++)
		for (j = 0; j <= len - i; j++)
		{
			if (judge(substring(str, j, i)) > maxlength)
			{
				maxlength = judge(substring(str, j, i));
				maxstr = substring(str, j, i);
			}
		}
	printf("字符串中第一次出现的最长回文字串是%s", maxstr);
	return 0;
}