#include <stdio.h>
typedef int ElementType;          //这里ElementType代表的是一个抽象的数据类型，这里为了防止出错，将其定义为整形。

typedef struct Node* ptrNode;
typedef ptrNode Stack;
struct Node
{
	ElementType Data;
	ptrNode Next
};

//检验栈是否为空函数
int
IsEmpty(Stack S)
{
	return S->Next == NULL;
}

//创建空栈函数
Stack
BuildStack(void)
{
	Stack S;

	S = (Stack)malloc(sizeof(struct Node));
	if (S == NULL)
		FatalError("Out of space!!!");
	S->Next == NULL;
	Empty(S);                //注意这里要将S清空。

	return S;
}

//清空栈的函数。
void
Empty(Stack S)
{
	if (S == NULL)
		Error("Must build Stack first!!!");
	while (!IsEmpty(S))          //因为S指向的是第一个节点的指针，只要存在栈，那么S就不是NULL，所以这里一定不能是(!S)。
		pop(S);                  //而且上面的if已经很清楚地对NULL进行了讨论。
}

//进栈的函数。
void
push(ElementType X, Stack S)
{
	ptrNode P;

	P = (ptrNode)malloc(sizeof(struct Node));
	if (P == NULL)
		FatalError("Out of space!!!");
	else
	{
		P->Data = X;
		P->Next = S->Next;
		S->Next = P;
	}
}

//出栈的函数。
ElementType
pop(Stack S)
{
	if (IsEmpty(S))
		Error("Empty Stack!!!");
	else
	{
		ElementType X;

		X = S->Next->Data;
		S->Next = S->Next->Next;
		free(S->Next);            //这里是自己加的，感觉要释放内存。如果不释放的话貌似变成懒惰的好像也说得通。

		return X;
	}

}
