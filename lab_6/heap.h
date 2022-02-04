#pragma once
#define DefaultSize 10;
#include<iostream>
using namespace std;
template <class Type> class MinHeap{
private:
     
    int currentSize; 
    int maxHeapSize; 
    void SiftDown(int start, int m); 
    void SiftUp(int start); 
public:
    Type* heap;
    MinHeap(int sz); 
    MinHeap(Type arr[], int n); 
    ~MinHeap() { delete[] heap; }
    bool Insert(const Type& x);  
    bool Remove(Type& x); 
    bool IsEmpty() const { return currentSize == 0; }
    bool IsFull() const { return currentSize == maxHeapSize; }
};
template <class Type> MinHeap <Type> ::
MinHeap(int sz) {
    maxHeapSize = sz;
    heap = new Type[maxHeapSize];
    if (heap == NULL) {
        cerr << "´æ´¢·ÖÅä´í£¡" << endl;  exit(1);
    }
    currentSize = 0;
}
template <class Type> MinHeap <Type> ::
MinHeap(Type arr[], int n) {
    maxHeapSize = n;
    heap = new Type[maxHeapSize];
    if (heap == NULL) { cerr << "´æ´¢·ÖÅä´í!" << endl;  exit(1); }
    for (int i = 0; i < n; i++)  heap[i] = arr[i]; 
    currentSize = n;  
    int currentPos = (currentSize - 2) / 2; 
    while (currentPos >= 0) {  
        SiftDown(currentPos, currentSize - 1);
        currentPos--;
    }
}
template <class Type> void MinHeap <Type> ::
SiftDown(int start, int m) {
    int i = start, j = 2 * i + 1;  
    Type temp = heap[i];
    while (j <= m) {
        if (j < m && heap[j] > heap[j + 1])
            j++;  
        if (temp <= heap[j])  break;
        else {
            heap[i] = heap[j];  
            i = j;  j = 2 * j + 1; 
        }
    }
    heap[i] = temp;
}
template <class Type> bool MinHeap <Type> ::
Insert(const Type& x) {
    if (currentSize == maxHeapSize) {
        cerr << "¶ÑÒÑÂú" << endl;  return false;
    }
    heap[currentSize] = x;  
    SiftUp(currentSize);  
    currentSize++;  
    return true;
}
template <class Type> void MinHeap <Type> ::
SiftUp(int start) {
    int j = start, i = (j - 1) / 2;  
    Type temp = heap[j];
    while (j > 0) {
        if (heap[i] <= temp)  break;  
        else { heap[j] = heap[i];  j = i;  i = (i - 1) / 2; }
    }
    heap[j] = temp;
}
template <class Type> bool MinHeap <Type> ::
Remove(Type& x) {
    if (currentSize == 0) { cout << "¶ÑÒÑ¿Õ" << endl;  return false; }
    x = heap[0];  
    heap[0] = heap[currentSize - 1];  
    currentSize--;
    SiftDown(0, currentSize - 1);  
    return true;
}

