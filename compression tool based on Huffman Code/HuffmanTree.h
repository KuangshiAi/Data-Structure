#pragma once
#include"MinHeap.h"
#include<vector>
#include<string>
using namespace std;
template <class Type> class HuffmanTree;
template <class Type> class HuffmanNode {
    friend class HuffmanTree<Type>;
public:
    Type data;//记录每个节点出现的频次，采用long long
    unsigned char elem;//每个节点所对应的字符
    string code;
    HuffmanNode <Type>* leftChild, * rightChild, * parent;
    HuffmanNode(Type fre=0,
        HuffmanNode <Type>* left = NULL,
        HuffmanNode <Type>* right = NULL,
        HuffmanNode <Type>* pr = NULL) :
        data(fre), leftChild(left), rightChild(right), parent(pr) 
    {
        elem = '*';
        code.clear();
    }
};
template <class Type> class HuffmanTree {
public:
    HuffmanNode <Type>* root;
    void MergeTree(HuffmanNode <Type>*& bt1,
        HuffmanNode <Type>*& bt2,
        HuffmanNode <Type>*& parent)
    {
        parent = new HuffmanNode<Type>();
        parent->leftChild = bt1;
        parent->rightChild = bt2;
        parent->data = bt1->data + bt2->data;
        bt1->parent = parent;
        bt2->parent = parent;
        parent->elem = '*';
    }
    void PreOrderCoding(HuffmanNode <Type>* root)
    {
        if (root == NULL)
            return;
        if (root->parent != NULL)
        {
            root->code = root->parent->code;
            if (root->parent->leftChild == root)
            {
                root->code +="0";
            }
            else
            {
                root->code += "1";
            }
        }
        PreOrderCoding(root->leftChild);
        PreOrderCoding(root->rightChild);
    }
    HuffmanTree(Type w[], int n)
    {
        MinHeap < HuffmanNode <Type>* > hp(n);
        HuffmanNode <Type>* parent, *first, *second,*work;
        parent = NULL;
        int validsize=0;
        for (int i = 0; i < n; i++) {
            if (w[i] != 0)
            {
                work=new HuffmanNode <Type>();
                work->data = w[i];  work->leftChild = NULL;
                work->rightChild = NULL;  work->parent = NULL;
                work->elem = i;
                hp.Insert(work);
                validsize++;
            }
        }
        for (int i = 0; i < validsize-1; i++) {
            parent = NULL;
            hp.Remove(first); 
            hp.Remove(second);
            MergeTree(first, second, parent);
            hp.Insert(parent);
        }
        root = parent;
    }
};
