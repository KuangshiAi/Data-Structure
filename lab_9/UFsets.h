#pragma once
const int DefaultSize = 30;
class UFSets {  
public:
    int* parent; 
    int size; 
    UFSets(int s = DefaultSize) { 
        size = s;  parent = new int[size];
        for (int i = 0; i < size; i++) parent[i] = -1;
    }
    ~UFSets() { delete[] parent; } 
    int Find(int x)
    {
        while (parent[x] >= 0)
        {
            x = parent[x];
        }
        return x;
    }
    void WeightedUnion(int Root1, int Root2)
    {
        int temp = parent[Root1] + parent[Root2];
        if (parent[Root2] < parent[Root1]) {
            parent[Root1] = Root2;  // Root2 中结点数多
            parent[Root2] = temp;  // Root1 指向 Root2
        }
        else {
            parent[Root2] = Root1;  // Root1 中结点数多
            parent[Root1] = temp;  // Root2 指向 Root1
        }
    }
    void Union(int Root1, int Root2) {
        // 将Root2连接到Root1下面
        parent[Root1] += parent[Root2];
        parent[Root2] = Root1;
    }
};
