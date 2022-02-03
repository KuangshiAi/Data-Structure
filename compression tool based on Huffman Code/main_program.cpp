#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include"HuffmanTree.h"
#include"MinHeap.h"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<stack>
#include <conio.h>
#include <Windows.h>
#include <winnt.h>
using namespace std;
void PreOrderextract(HuffmanNode<long long>* root, char* Huffmancode[], vector<unsigned char>& validnode)
{
	if (root == NULL)
		return;
	if (root->leftChild==NULL&&root->rightChild==NULL)
	{
		strcpy(Huffmancode[root->elem], root->code.c_str());
		validnode.push_back(root->elem);
	}
	PreOrderextract(root->leftChild, Huffmancode,validnode);
	PreOrderextract(root->rightChild, Huffmancode,validnode);
}
int getdotpos(string filename)//获取文件名中“.”最后一次出现的位置
{
	int i = 0;
	int pos = -1;
	for (i = 0; i < filename.size(); i++)
	{
		if (filename[i] == '.')
			pos = i;
	}
	return pos;
}
long long fsize(string filename)//编译器把long当成int，导致ftell函数不够用
{
	long long size;
	FILE* fp = fopen(filename.c_str(), "rb");
	FILE* fq = fp;
	fpos_t posthead;//存储文件指针位置 
	fpos_t postend;
	fseek(fp, 0, SEEK_SET);//定位在文件开头 
	fgetpos(fp, &posthead);
	fseek(fq, 0, SEEK_END);//定位在文件尾部 
	fgetpos(fq, &postend);
	size= postend - posthead;
	return size;
}
unsigned char transfer(string bincode)//将二进制字符串转化为十进制字符
{
	unsigned char temp = 0;
	for (int j = 0; j < 8; j++) {
		if (bincode[j] == '1')
		{
			temp += pow(2, 7 - j);
		}
	}
	return temp;
}
string transfer_back(unsigned char x)//将十进制字符转化为二进制字符串
{
	if (x == 0) {
        return "00000000";
    }
    string ret;
    stack<char> st;
	int i = 0;
    while (x > 0) {
        if (x % 2 == 1) {
            st.push('1');
        } else {
            st.push('0');
        }
        x /= 2;
		i++;
    }
	while (i < 8)
	{
		st.push('0');
		i++;
	}
    while (!st.empty()) {
        ret.push_back(st.top());
        st.pop();
    }
    return ret;
}
bool copyfile(const char* filename, const char* fileout)
{
	char buff[1024];
	FILE* fp_filename = fopen(filename, "rb");
	FILE* fp_fileout = fopen(fileout, "wb");
	if (!fp_filename)
	{
		printf("读取文件打开失败\n");
		return false;
	}
	if (!fp_fileout)
	{
		printf("目标文件打开失败\n");
		return false;
	}
	while (!feof(fp_filename))
	{
		int len = fread(buff, sizeof(char), sizeof(buff), fp_filename);
		fwrite(buff, sizeof(char), len, fp_fileout);
	}
	fclose(fp_filename);
	fclose(fp_fileout);
	return true;
}
bool compress(string filename, string outputfile)
{
	clock_t start, finish;
	start = clock();
	long long w[256] = {0};
	unsigned char ch;
	FILE* ifp;
	if ((ifp = fopen(filename.c_str(), "rb")) == NULL)
	{
		printf("文件不能打开\n");
		return false;
	}
	long long file_len = 0;//文件长度
	int validsize = 0;//文件中有效节点个数
	fread(&ch, 1, 1, ifp);
	while (!feof(ifp))
	{
		w[ch]++;
		file_len++;
		fread(&ch, 1, 1, ifp);
	}
	fclose(ifp);
	for (int i = 0; i < 256; i++)
	{
		if (w[i] > 0)
			validsize++;
	}
	HuffmanTree<long long>T(w, 256);
	T.PreOrderCoding(T.root);
	char* Huffmancode[256];//用以存放十进制下是i的节点的霍夫曼编码（字符串指针）
	for (int i = 0; i < 256; i++)
	{
		Huffmancode[i] = new char[256];
		Huffmancode[i][0] = '\0';
	}
	vector<unsigned char>validnode;
	PreOrderextract(T.root, Huffmancode,validnode);
	FILE* ofp;
	if ((ofp = fopen(outputfile.c_str(), "wb")) == NULL)
	{
		printf("未能成功创建压缩文件\n");
		return false;
	}
	fprintf(ofp, "%d,%s,", filename.size()-getdotpos(filename),filename.substr(getdotpos(filename)).c_str());//写入原文件的拓展名长度和拓展名
	fprintf(ofp, "%lld,%d,",file_len,validsize);//写入文件长度和有效节点总数
	fprintf(ofp,"%d,%s",filename.size(),filename.c_str());//写入原文件名长度和文件名
	while (!validnode.empty())//写入有效节点对应的字符和出现频次
	{
		fprintf(ofp, "%c,%lld,", validnode.back(), w[validnode.back()]);
		validnode.pop_back();
	}
	if ((ifp = fopen(filename.c_str(), "rb")) == NULL)
	{
		printf("文件不能打开\n");
		return false;
	}
	string buff;
	fread(&ch, 1, 1, ifp);
	while (1)
	{
		while (!feof(ifp)&&buff.length() < 8)
		{   
			buff += Huffmancode[ch];
			fread(&ch, 1, 1, ifp);
		}
		int i = 0;
		if (buff.size() >= 8)
		{
			while (8 * i <= buff.size() - 8)
			{
				unsigned char temp = transfer(buff.substr(8 * i, 8));
				fwrite(&temp, 1, 1, ofp);
				i++;
			}
			if (buff.size() % 8)
			{
				string temp = buff.substr(8 * i);
				buff.clear();
				buff = temp;
			}
			else
			{
				buff.clear();
			}
		}
		if (feof(ifp))
			break;
	}
	if (!buff.empty())//剩下的部分补足八位以后写入文件
	{
		buff += "00000000";
		unsigned char temp = transfer(buff.substr(0, 8));
		fwrite(&temp,1,1, ofp);
	}
	fclose(ifp);
	fclose(ofp);
	finish = clock();
	printf("文件压缩成功！\n");
	long long num = 100;
	printf("文件压缩后是原文件大小的%lld%%\n", fsize(outputfile)*num/fsize(filename));
	double duration = ((double)finish - (double)start) / CLOCKS_PER_SEC;
	printf("文件压缩时间为%fs\n",duration);
	return true;
}
bool uncompress(string filename,string outputfile)
{
	clock_t start, finish;
	start = clock();
	FILE* ifp;
	FILE* ofp;
	if ((ifp = fopen(filename.c_str(), "rb")) == NULL)
	{
		printf("文件不能打开\n");
		return false;
	}
	int sufname_len;
	fscanf(ifp, "%d,", &sufname_len);
	char *dat_file_extension=new char[sufname_len+1];
	strcpy(dat_file_extension, "");
	fread(dat_file_extension,1,sufname_len,ifp);
	dat_file_extension[sufname_len] = '\0';
	outputfile += dat_file_extension;
	delete[]dat_file_extension;
	int validsize;
	long long file_len;
	fscanf(ifp, ",%lld,%d,", &file_len, &validsize);
	int filename_len;
	fscanf(ifp, "%d,", &filename_len);
	char *ori_filename=new char[filename_len+1];
	fread(ori_filename, 1, filename_len, ifp);
	ori_filename[filename_len] = '\0';
	long long w[256] = { 0 };
	for (int i = 0; i < validsize; i++)//读取压缩文件中各有效节点出现频次到w数组中
	{
		unsigned char temp;
		fscanf(ifp, "%c,", &temp);
		fscanf(ifp, "%lld,", &w[temp]);
	}
	HuffmanTree<long long>T(w, 256);//重构霍夫曼树
	T.PreOrderCoding(T.root);
	if ((ofp = fopen(outputfile.c_str(), "wb")) == NULL)
	{
		printf("未能成功创建解压缩文件\n");
		return false;
	}
	string buff;
	unsigned char ch;
	fread(&ch, 1, 1, ifp);
	HuffmanNode<long long>* current;
	current = T.root;
	long long count_len=0;
	while (1)
	{
		while (!feof(ifp)&&buff.size() < validsize )
		{
			buff += transfer_back(ch);
			fread(&ch, 1, 1, ifp);
		}
		//根据buff的指引把Huffman解码，找到原码以后输出
		int i = 0;
		while (i < buff.size())
		{
			if (current != NULL && current->leftChild == NULL && current->rightChild == NULL)//访问到了叶子节点
				{
					fwrite(&current->elem, 1, 1, ofp);
					current = T.root;
					count_len++;
				}
			if (current != NULL)
				{
					if (buff[i] == '0')
						current = current->leftChild;
					else
						current = current->rightChild;
					i++;
				}
			if (count_len == file_len)
				break;
		}
		buff.clear();
	   if (feof(ifp))
		    break;
	}
	fclose(ifp);
	fclose(ofp);
	finish = clock();
	printf("原文件%s解压缩成功！\n",ori_filename);
	long long num = 100;
	double duration = ((double)finish - (double)start) / CLOCKS_PER_SEC;
	printf("文件解压缩时间为%fs\n", duration);
	return true;
}
int main()
{
	printf("欢迎使用Huffman Code压缩文件及解压缩文件工具\n");
	char* option[2];
	option[0] = new char[14];
	strcpy(option[0], "1.compress");
	option[1] = new char[14];
	strcpy(option[1], "2.uncompress");
	char key = 0;
	int i, select = 0;
	HANDLE ohandle = GetStdHandle(STD_OUTPUT_HANDLE);
	while (true) {
		for (i = 0; i < 2; i++) {//这里共2个选项
			if (i == select)//设置焦点高亮
				SetConsoleTextAttribute(ohandle, BACKGROUND_INTENSITY);
			else if (i == select + 1)//恢复设置
				SetConsoleTextAttribute(ohandle, FOREGROUND_INTENSITY);
			puts(option[i]);
		}
		SetConsoleTextAttribute(ohandle, FOREGROUND_INTENSITY);//恢复设置
		key = _getch();
		if (key == 0x1b)  //ESC 键
			return 0;
		if (key == 0xd)  //Enter 键
			break;
		if (key < 0) {  //非ascii码键2个字节
			key = _getch();
			switch (MapVirtualKey(key, 1)) {
			case VK_UP:
				select = (select + 3) % 2;//焦点上移，减一，滚动选择，共2个选项
				break;
			case VK_DOWN:
				select = (select + 1) % 2;//焦点下移，加一
				break;
			}
		}
		system("cls");
	}
	system("cls");
	printf("you selected : %s\n", option[select]);
	if(select==0)
	{
		printf("请输入需要压缩的文件名（包括拓展名）\n");
		string filename;
		string outputfile;
		getline(cin, filename);
		printf("请输入压缩后的文件名（包括拓展名）\n");
		getline(cin, outputfile);
		compress(filename, outputfile);
	}
	if (select == 1)
	{
		printf("请输入需要解压缩的文件名（包括拓展名）\n");
		string filename;
		string outputfile;
		getline(cin, filename);
		printf("请输入解压缩后的文件名（不包括无效的后缀）\n");
		getline(cin, outputfile);
		uncompress(filename, outputfile);
	}
	return 0;
}
