#pragma once
class Queue {
private:
    int rear, front;
    char* elements;
    int size;
public:
    Queue(int sz = 40)
    {
        elements = new char[40];
        front = rear = 0;
        size = sz;
    }
    ~Queue() { delete[] elements; }
    int EnQueue(char x)
    {
        if (!isFull())
        {
            rear = (rear + 1) % size;
            elements[rear] = x;
            return 1;
        }
        else
            return 0;
    }
    int DeQueue()
    {
        if (isEmpty())
            return 0;
        else
        {
            front = (front + 1) % size;
            return 1;
        }
    }
    int GetFront(char& x)
    {
        if (isEmpty())
            return 0;
        else
        {
            x = elements[(front + 1) % size];
            return 1;
        }
    }
    int isFull()
    {
        if (((rear + 1) % size )== front)
            return 1;
        else
            return 0;
    }
    int isEmpty()
    {
        if (rear == front)
            return 1;
        else
            return 0;
    }
};