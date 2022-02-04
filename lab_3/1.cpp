#include<stdio.h>
#include"stack.h"
int main()
{
	stack_a* p = new stack_a();
	p->push(5);
	p->push(15);
	p->push(2);
	printf("getMin:%d\n", p->getMin());
	printf("pop:%d\n", p->gettop());
	p->pop();
	printf("getMin:%d\n", p->getMin());
	return 0;
}