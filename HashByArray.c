#include <stdio.h>
#define MinTableSize 50
typedef int ElementType;
typedef struct cell* cell;
typedef int Position;
typedef struct HashTable* Hash;

enum State { Legitimate, Empty, Deleted };

struct cell
{
	ElementType Data;
	enum State Info;   //用来记录这个单元是已经用了还是空的或者是被删除的，这里是采用懒惰删除的，假装删除。
};

struct HashTable
{
	int TableSize;
	cell Array;           //用来存储cell的数组。
};

//初始化函数。
Hash
Initialize(int tablesize)
{
	Hash H;
	int i;

	if (tablesize < MinTableSize)
	{
		Error("tablesize is too small!!!");
		return;
	}
	
	H = (Hash)malloc(sizeof(struct HashTable));
	if (H == NULL)
		FatalError("Out of space!!!");
	else
	{
		H->TableSize = NextPrime(tablesize);
		H->Array = (cell)malloc(sizeof(struct cell) * H->TableSize);
		if (H->Array == NULL)
			FatalError("Out of space!!!");
		else
		{
			for (i = 0; i < H->TableSize; i++)
				H->Array[i].Info = Empty;
		}
	}
	return H;
}

//查找函数。
Position
Find(ElementType X, Hash H)
{
	Position P;
	int initc = 0;

	P = Hashdef(X, H->TableSize);     //这里hashdef函数是用来记录关键字的，我们就假定关键字和下标是一致的。
	while (H->Array[P].Info != Empty && H->Array[P].Data != X)
	{
		P += 2 * (++initc) - 1;   //先移1，再移3，再移5，这样看上去就是从最开始移动了1，4，9……，即平方探测法。
		if (P >= H->TableSize)   //要注意本来的initc要实现自加，然后P要实现累加。
			P -= H->TableSize;  //当下标等于最大数量的时候，因为是下标，所以这个时候就已经超了，所以减掉之后就变成了前面的。
	}
	return P;
}

//插入函数。
void
Insert(ElementType X, Hash H)
{
	Position P;

	P = Find(X, H);
	if (H->Array[P].Info != Legitimate)  //注意这里使用的是不等于，而不能仅仅是等于Empty，因为还有一个Deleted。
	{
		H->Array[P].Data = X;
		H->Array[P].Info = Legitimate;
	}
}
