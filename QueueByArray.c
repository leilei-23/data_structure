#include <stdio.h>
#define Maxsize 1000
typedef int ElementType;


struct QueueRecode         //队列：先进先出。
{
	int front;              //前指针，用来删除前面的元素。向后移一位，则删除移动之后所在位置的元素。
	int rear;               //后指针，用来再队列后面添加元素。向后移一位则在移动后的位置上添加一个元素。
	ElementType Array[Maxsize];  //数组，用来存储数据。
};
typedef struct QueueRecode* ptrQueue;
typedef ptrQueue Queue;

//使队列为空的函数。
void
MakeEmpty(Queue Q)
{
	Q->front = Q->rear;
}

//验证队列是否为空的函数。
void
IsEmpty(Queue Q)
{
	return (Q->rear == Q->front);
}

//队列中添加元素的函数。
void
QAdd(Queue Q, ElementType X)
{
	if ((Q->rear + 1) % Maxsize == Q->front)   //一定要注意这里，当rear逐渐后移移动到最大位置时，将继续向数组前面进行插入。
		Error("Full Queue!!!");                //所以这里要取余，记住什么条件下数组是满的，以及后面什么条件下数组是空的。
	else	
		Q->Array[(++Q->rear) % Maxsize] = X;
}

//队列中删除元素的函数。
ElementType
Delete(Queue Q)
{
	if (Q->front == Q->rear)
		Error("Empty Queue!!!");
	else
		return Q->Array[(++Q->front) % Maxsize];
}
