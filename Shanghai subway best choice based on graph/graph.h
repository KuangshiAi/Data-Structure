#pragma once
#include<stdio.h>
template <class DistType> class Graph;
template <class DistType> class EdgeNode {  // �߽����ඨ��
    friend class Graph <DistType>;
public:
    int dest;  // �ߵ���һ����λ��
    DistType cost;  // ���ϵ�Ȩֵ
    int line;//��һ�����Ǽ����ߵı�
    EdgeNode <DistType>* link;  // �߽����ָ��
    EdgeNode() { }  // ���캯��
    EdgeNode(int line_num,int d, DistType c) : dest(d), cost(c), link(NULL),line(line_num) { }
};
template <class DistType> class VertexNode {
    friend class EdgeNode <DistType>;
    friend class Graph <DistType>;
public:
    int data;  // ��������
    EdgeNode <DistType>* adj;  // ���߱�ı�ͷָ��
    VertexNode()
    { 
        data = -1;
        adj = NULL;
    }
    VertexNode(int name)
    {
        data = name;
        adj = NULL;
    }
};
template < class DistType> class Graph {
public:
    VertexNode <DistType>* NodeTable;  // �����
    int VerticesNum;  // ��ǰ������
    int VerticesMaxNum;  // ��󶥵���
    int EdgesNum;  // ��ǰ����
    Graph(int size)// ���캯��
    {
        NodeTable = new VertexNode<DistType>[size];
        VerticesNum = 0;
        EdgesNum = 0;
        VerticesMaxNum = size;
    }
    ~Graph()  // ��������
    {
        VerticesNum = 0;
        EdgesNum = 0;
        VerticesMaxNum = 0;
        delete[]NodeTable;
    }
    int GraphEmpty() { return VerticesNum == 0; }  // ��ͼ�շ�
    int VerticesNumber() { return VerticesNum; }  // ����ͼ�Ķ�����
    int EdgesNumber() { return EdgesNum; }  // ����ͼ�ı���
// ������(v1, v2)�ϵ�Ȩ
    DistType GetWeight(int v1, int v2)
    {
        if (v1 != -1 && v2 != -1) {
            EdgeNode <DistType>* p = NodeTable[v1].adj;  // ������ͷָ��
            while (p != NULL)
            {
                if (p->dest == v2)
                    return p->cost;  // �ҵ���Ӧ�ߣ�����Ȩֵ
                else p = p->link;  // ��������һ����
            }
        }
        return 0;
    }
    //������(v1,v2)��������һ���ߵ�
    int GetLine(int v1, int v2)
    {
        if (v1 != -1 && v2 != -1) {
            EdgeNode <DistType>* p = NodeTable[v1].adj;  // ������ͷָ��
            while (p != NULL)
            {
                if (p->dest == v2)
                    return p->line;  // �ҵ���Ӧ�ߣ�����Ȩֵ
                else p = p->link;  // ��������һ����
            }
        }
        return 0;
    }
    // ��������v�ĵ�һ���ڽӶ���
    int GetFirstNeighbor(int v)
    {
        // ����������򷵻�-1
        if (v != -1) {  // v����
            EdgeNode <DistType>* p = NodeTable[v].adj;  // ������ͷָ��
            if (p != NULL)
                // ����һ���ڽӶ�����ڣ��򷵻ظñߵ���һ������
                return p->dest;
        }
        return -1;  // �������ڣ��򷵻�-1
    }
    // ��������v1��ĳ�ڽӶ���v2�����һ���ڽӶ���
    int GetNextNeighbor(int v1, int v2)
    {
        // ��û����һ���ڽӶ����򷵻�-1
        if (v1 != -1) {  // v1����
            EdgeNode <DistType>* p = NodeTable[v1].adj;  // ������ͷָ��
            while (p != NULL) {  // Ѱ��ĳ�ڽӶ���v2
                if (p->dest == v2 && p->link != NULL)
                    return p->link->dest;
                else p = p->link;
            }
        }
        return -1;
    }
    // �����¶���vertex
    void InsertVertex(int vertex)
    {
        if (VerticesNum == VerticesMaxNum)
        {
            printf("ͼ����\n");
            return;
        }
        NodeTable[vertex].data=vertex;
        NodeTable[vertex].adj = NULL;
        VerticesNum++;
    }
    // ����ȨΪweight���±�(v1, v2)
    void InsertEdge(int v1, int v2,int line_num,DistType weight)
    {
        if (v1 != -1 && v2 != -1)
        {
            if (NodeTable[v1].data == -1)
            {
                InsertVertex(v1);
            }
            if (NodeTable[v2].data == -1)
            {
                InsertVertex(v2);
            }
            EdgeNode <DistType>* p = NodeTable[v1].adj;
            if (p == NULL)
            {
                EdgeNode<DistType>*temp = new EdgeNode<DistType>(line_num,v2, weight);
                NodeTable[v1].adj = temp;
            }
            else
            {
                while (p->link != NULL)
                    p = p->link;
                EdgeNode<DistType>* temp = new EdgeNode<DistType>(line_num,v2, weight);
                p->link = temp;
            }
            EdgesNum++;
        }
    }
};
