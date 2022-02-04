#pragma once
#include<stdio.h>
#define maxsize 100
class stack_b;
class stack_a
{
private:
	int elements[maxsize];
	int top;
	stack_b* rs;
public:
	stack_a();
	~stack_a() { delete[]elements; delete rs; }
	int push(int x);
	int pop();
	int gettop();
	int getMin();

};
class stack_b
{
private:
	int data[maxsize];
	int top;
public:
	stack_b();
	~stack_b() { delete[]data; }
	int push(int x);
	int pop();
	int gettop();
};
stack_b::stack_b()
{
	top = -1;
}
stack_a::stack_a()
{
	top = -1;
	rs = new stack_b();
}
int stack_a::push(int x)
{
	if (top < maxsize - 1)
	{
		if (top == -1)
			rs->push(0);
		else if (x < getMin())
			rs->push(top + 1);
		else
			rs->push(rs->gettop());
		this->elements[++top] = x;
		return 1;
	}
	else
		return 0;
}
int stack_a::pop()
{
	if (top < 0)
		return 0;
	else
	{
		top--;
		rs->pop();
		return 1;
	}
}
int stack_a::gettop()
{
	if (top >= 0)
		return elements[top];
	else
		printf("у╩ря©у\n");
}
int stack_a::getMin()
{
	if (top >= 0)
		return elements[rs->gettop()];
	else
		printf("у╩ря©у\n");
}
int stack_b::push(int x)
{
	if (top < maxsize - 1)
	{
		data[++top] = x;
		return 1;
	}
	else
		return 0;
}
int stack_b::pop()
{
	if (top < 0)
		return 0;
	else
	{
		top--;
		return 1;
	}
}
int stack_b::gettop()
{
	return data[top];
}
