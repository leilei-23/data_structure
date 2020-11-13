#include <stdio.h>
typedef int ElementType;
typedef struct Node* PtrNode;
typedef PtrNode List;
typedef PtrNode Position;
typedef struct HashTable* Hash;
#define MinTableSize 50

struct Node
{
	ElementType Data;   //链表的节点
	PtrNode Next;
};

struct HashTable
{
	int TableSize;  //哈希表包含两部分，一部分是表的大小，另一部分是存储指向链表的头指针的数组。因为数组的表达形式
	List* ListArray; //可以用指向数组第一个元素的指针表示，所以这也就是指向指针的指针，这里要好好理解。
};

//初始化函数。
Hash
Initialize(int tablesize)
{
	if (tablesize < MinTableSize)
	{
		Error("tablesize is small!!!");
		return NULL;
	}
	Hash H;
	int i;

	H = (Hash)malloc(sizeof(struct HashTable));//这里申请空间的方式，以及后面的方式需要好好想一想。
	if (H == NULL)
		FatalError("Out of space!!!");
	else
	{
		H->TableSize = NextPrime(tablesize);   //NextPrime函数是用来计算tablesize的下一个素数，因为证明过哈希表的大小是素数比较好。
		H->ListArray = (List*)malloc(H->TableSize * sizeof(List));//这里申请空间的方式，以及后面的方式需要好好想一想。
		if (H->ListArray == NULL)
			FatalError("Out of space!!!");
		for (i = 0; i < H->TableSize; i++)
		{
			H->ListArray[i] = (List*)malloc(sizeof(struct Node));//这里申请空间的方式，以及后面的方式需要好好想一想。
			if (H->ListArray[i] == NULL)
				FatalError("Out of space!!!");
			else
				H->ListArray[i]->Next == NULL;//初始化所以就让每个链表指向NULL即可。
		}
	}

	return H;
}

//查找函数。
Position
Find(ElementType X, Hash H)
{
	List L;
	Position P;

	L = H->ListArray[Hashdef(X, H->TableSize)];//这里的函数是用来计算关键字的，这里没有给出函数，一般可用取余来做。
	P = L->Next;  //注意返回的是位置，而L只是一个头指针，并不能代表位置，所以应向后移一位，使其对应在位置上。
	while (P != NULL && P->Data != X)
		P = P->Next;
	return P;
}

//插入函数。
void
Insert(ElementType X, Hash H)
{
	Position P;
	PtrNode Temp;
	List L;

	P = Find(X, H); //注意这里应该先查找一下，若存在的话就不要插入了，也是属于对边界情况的讨论。
	if (P == NULL)
	{
		Temp = (PtrNode)malloc(sizeof(struct Node));
		if (Temp == NULL)
			FatalError("Out of space!!!");
		else 
		{
			Temp->Data = X;
			L = H->ListArray[Hashdef(X, H->TableSize)];
			Temp->Next = L->Next;
			L->Next = Temp;
		}
		
	}
}
