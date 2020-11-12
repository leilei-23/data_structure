#include <stdio.h>
typedef int ElementType; //ElementType指的是抽象的数据结构。这里为了防止报错定义成int。
typedef struct StackStruct* stack;
struct StackStruct           //创建结构体
{
	int Capacity;         //数组的最大容量
	int size;             //当前的下标，从0开始
	ElementType* Array;   //用来存储数据的数组
};

//是否为空的函数
int
IsEmpty(stack S)
{
	return S->size == -1;
}

//创建空栈的函数。
void
CreatStack(stack S)
{
	S->size == -1;
}

//进栈函数。
void
push(ElementType X, stack S)
{
	if (S->size == S->Capacity + 1)
		Error("Stack is full!!!");
	else
	{
		S->Array[++S->size] = X;        //这种写法值得参考。
	}
}

//出栈的函数。
ElementType
pop(stack S)
{
	ElementType Temp;

	if (IsEmpty(S))
		Error("Empty stack!!!");
	else
	{
		return Temp = S->Array[S->size--];
	}
}
