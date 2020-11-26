#include <stdio.h>
#define  ElementType int
#define MinHeapSize 5
#define MinValue 1
typedef struct HeapStruct* PriorityQueue;

struct HeapStruct
{
	int Capacity;       
	int size;
	ElementType* Elements;            //用数组来表示
};

PriorityQueue
Initialize(int Maxsize)
{
	PriorityQueue H;

	if (Maxsize < MinHeapSize)
		Error("Too small Heap");
	H = malloc(sizeof(struct HeapStruct));
	if (H == NULL)
		FatalError("Out of space!!!");

	H->Elements = malloc(sizeof(ElementType) * (Maxsize + 1));//多出来的1用来放置哨兵
	H->Capacity = Maxsize;
	H->size = 0;
	H->Elements[0] = MinValue;         //设置哨兵

	return H;
}

void
Insert(ElementType X, PriorityQueue H)
{
	int i;

	if (H->size == H->Capacity)
		Error("The Heap Is Full!!!");
	
	for (i = ++H->size; H->Elements[i / 2] > X; i = i / 2)
		H->Elements[i] = H->Elements[i / 2];        //上滤
	H->Elements[i] = X;
}

ElementType
Delete(PriorityQueue H)
{
	int i;
	int child;
	ElementType MinV;
	ElementType LastValue;

	if (H->size == 0)
		Error("The Heap Is Empty!!!");
	MinV = H->Elements[0];
	LastValue = H->Elements[H->size--];
	for (i = 1; 2 * i <= H->size; i = child)
	{
		child = 2 * i;
		if (child != H->size && H->Elements[child] > H->Elements[child + 1])
			child = child + 1;     //取左右孩子中较小的
		if (H->Elements[child] < LastValue)
			H->Elements[i] = H->Elements[child];//下滤
		else
			break;
	}
	H->Elements[i] = LastValue;

	return MinV;
}
