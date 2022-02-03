#pragma once
#include<stdio.h>
template <class DistType> class Graph;
template <class DistType> class EdgeNode {  // 边结点的类定义
    friend class Graph <DistType>;
public:
    int dest;  // 边的另一顶点位置
    DistType cost;  // 边上的权值
    int line;//这一条边是几号线的边
    EdgeNode <DistType>* link;  // 边结点后继指针
    EdgeNode() { }  // 构造函数
    EdgeNode(int line_num,int d, DistType c) : dest(d), cost(c), link(NULL),line(line_num) { }
};
template <class DistType> class VertexNode {
    friend class EdgeNode <DistType>;
    friend class Graph <DistType>;
public:
    int data;  // 顶点名字
    EdgeNode <DistType>* adj;  // 出边表的表头指针
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
    VertexNode <DistType>* NodeTable;  // 顶点表
    int VerticesNum;  // 当前顶点数
    int VerticesMaxNum;  // 最大顶点数
    int EdgesNum;  // 当前边数
    Graph(int size)// 构造函数
    {
        NodeTable = new VertexNode<DistType>[size];
        VerticesNum = 0;
        EdgesNum = 0;
        VerticesMaxNum = size;
    }
    ~Graph()  // 析构函数
    {
        VerticesNum = 0;
        EdgesNum = 0;
        VerticesMaxNum = 0;
        delete[]NodeTable;
    }
    int GraphEmpty() { return VerticesNum == 0; }  // 判图空否
    int VerticesNumber() { return VerticesNum; }  // 返回图的顶点数
    int EdgesNumber() { return EdgesNum; }  // 返回图的边数
// 给出边(v1, v2)上的权
    DistType GetWeight(int v1, int v2)
    {
        if (v1 != -1 && v2 != -1) {
            EdgeNode <DistType>* p = NodeTable[v1].adj;  // 边链表头指针
            while (p != NULL)
            {
                if (p->dest == v2)
                    return p->cost;  // 找到对应边，返回权值
                else p = p->link;  // 否则找下一条边
            }
        }
        return 0;
    }
    //给出边(v1,v2)是属于哪一条线的
    int GetLine(int v1, int v2)
    {
        if (v1 != -1 && v2 != -1) {
            EdgeNode <DistType>* p = NodeTable[v1].adj;  // 边链表头指针
            while (p != NULL)
            {
                if (p->dest == v2)
                    return p->line;  // 找到对应边，返回权值
                else p = p->link;  // 否则找下一条边
            }
        }
        return 0;
    }
    // 给出顶点v的第一个邻接顶点
    int GetFirstNeighbor(int v)
    {
        // 如果不存在则返回-1
        if (v != -1) {  // v存在
            EdgeNode <DistType>* p = NodeTable[v].adj;  // 边链表头指针
            if (p != NULL)
                // 若第一个邻接顶点存在，则返回该边的另一个顶点
                return p->dest;
        }
        return -1;  // 若不存在，则返回-1
    }
    // 给出顶点v1的某邻接顶点v2后的下一个邻接顶点
    int GetNextNeighbor(int v1, int v2)
    {
        // 若没有下一个邻接顶点则返回-1
        if (v1 != -1) {  // v1存在
            EdgeNode <DistType>* p = NodeTable[v1].adj;  // 边链表头指针
            while (p != NULL) {  // 寻找某邻接顶点v2
                if (p->dest == v2 && p->link != NULL)
                    return p->link->dest;
                else p = p->link;
            }
        }
        return -1;
    }
    // 插入新顶点vertex
    void InsertVertex(int vertex)
    {
        if (VerticesNum == VerticesMaxNum)
        {
            printf("图已满\n");
            return;
        }
        NodeTable[vertex].data=vertex;
        NodeTable[vertex].adj = NULL;
        VerticesNum++;
    }
    // 插入权为weight的新边(v1, v2)
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
