typedef int ElementType;
#include <stdio.h>

struct Node                     //定义节点，包括两部分，一部分存储数据，一部分指向下一个节点。
{
	ElementType Data;
	struct Node* Next;
};
typedef struct Node* ptrNode;

struct QNode             //两个指针，前指针用来删除元素，后指针用来插入元素，因为队列是先进先出，后进后出。
{
	ptrNode front;
	ptrNode rear;
};

typedef struct QNode* Queue;
//删除函数
ElementType
Delete(Queue Q)
{
	if (Q->front == NULL)
		Error("Empty Queue!!!");         
	else 
	{
		ptrNode Temp;
		ElementType temp;

		Temp = Q->front;
		if (Q->front == Q->rear)
			Q->front = Q->rear = NULL;
		else
			Q->front = Q->front->Next;
		temp = Temp->Data;
		free(Temp);           //及时释放空间。

		return temp;
	}
}

//插入函数。
void
Insert(Queue Q, ElementType X)
{
	ptrNode P;

	P = (ptrNode)malloc(sizeof(struct Node));   //申请空间构造节点。
	P->Data = X;
	P->Next = NULL;
	Q->rear = P;
}
