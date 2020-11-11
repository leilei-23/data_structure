#include <stdlib.h>
typedef int ElementType;  //这里为了防止程序报错，将ElementType定义成了代表整形，它其实是一个抽象得数据类型概念，可以代表任何类型。

struct LNode
{
	ElementType  Element;
	struct LNode* Next;
};

typedef struct LNode* Position;  //这种定义方式需要学会，虽然都代表指向节点的指针，但是一个代表的是指向链表的头结点的指针，即能
typedef struct LNode* List;      //代表链表，而另一个是要代表链表中具体位置的指针。

//创建一个链表
List set(List L)
{
	List PtoL;

	L = (List)malloc(sizeof(struct LNode));
	L->Next = NULL;

	return PtoL;
}

//验证一个链表是否为空
int
IsEmpty(List L)   //学会使用这种定义函数的方式，返回的类型在上面，函数以及形参在下面。
{
	return L->Next == NULL;
}

//查找函数
Position
Find(ElementType X, List L)
{
	Position P;
	P = L->Next;
	while (P != NULL && P->Element != X)
		P = P->Next;
	
	return P;
}

//判断一个数据是不是链表最后一个数据
int
IsLast(Position P, List L)
{
	return P->Next == NULL;
}

//查找数值X位置的前一个的位置。
Position
FindPrevious(ElementType X, List L)
{
	Position P;

	P = L;
	while (P->Next->Element != X && P->Next != NULL)
		P = P->Next;

	return P;
}
//删除某个值对应的一个节点。
void
Delete(ElementType X, List L)
{
	Position P, Temp; //注意这里加了一个临时变量，用来得到P的下一个变量。

	P = FindPrevious( X, L);
	if (P->Next != NULL)
	{
		Temp = P->Next;
		P->Next = Temp->Next;

		free(Temp);   //注意这里应该保持一个释放空间的好习惯。
	}  
}

//在指定位置插入一个指定数值的节点。
void
InsertList(ElementType X, List L, Position P)
{
	Position Temp;

	Temp = (Position)malloc(sizeof(struct LNode));  //通过申请一个新的空间生成一个新的节点。
	if (Temp == NULL)
		FatalError("Out of space!!!");    //这一句要学着加上去，因为应该考虑到申请内存空间不成功的时候。
	Temp->Element = X;
	Temp->Next = P->Next;
	P->Next = Temp;
}

//删除一个链表。
void
DeleteL(List L)
{
	Position P,Temp;
	P = L->Next;
	L->Next = NULL;
	while (P->Next != NULL)
	{
		Temp = P->Next;  //从前之后依次释放空间
		free(P);
		P = Temp;
	}
}
