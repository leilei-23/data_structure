#include <stdio.h>
typedef int ElementType;
typedef struct AVLNode* AVLTree;
typedef struct AVLNode* Position;

struct AVLNode
{
	ElementType Data;  //平衡二叉树必须首先是二叉树，小的放左子树，大的放右子树，所以必须要有指向左子树和右子树的指针。
	AVLTree Left;     //平衡二叉树是指任意节点的左右的高度差的绝对值都要小于2，所以必须有一个高度来记录。
	AVLTree Right;      
	int Height;
};

//计算高度函数。
static int
GetHeigth(Position P)
{
	if (P == NULL)
		return -1;
	else
		return P->Height;
}

//左单次旋转函数（左左旋转）
AVLTree
SingleRoatingLeft(AVLTree K2)
{
	Position K1;

	K1 = K2->Left;
	K2->Left = K1->Right;       //结合笔记的图更好理解一些。
	K1->Right = K2;
	K2->Height = Max(GetHeigth(K2->Left), GetHeigth(K2->Right)) + 1;   //这里一定注意要使用GetHeigth函数，因为递归到最后的
	K1->Height = Max(GetHeigth(K1->Left), K2->Height) + 1;             //的时候将出现NULL，没有Height这个结构

	return K1;
}

//右单次旋转函数（右右旋转）
AVLTree
SingleRoatingRight(AVLTree K2)
{
	Position K1;

	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;
	K2->Height = Max(GetHeigth(K2->Left), GetHeigth(K2->Right)) + 1;
	K1->Height = Max(GetHeigth(K1->Right), K2->Height) + 1;

	return K1;
}

//左双次旋转函数（左右旋转）
AVLTree
DoubleRoatingLeft(AVLTree K3)
{
	K3->Left = SingleRoatingRight(K3->Left);//结合笔记去理解这里为什么是进行两次旋转，之后要记住左右旋转就是先右再左单次旋转。
	return SingleRoatingLeft(K3);
}

//右双次旋转函数（右左旋转）
AVLTree
DoubleRoatingRight(AVLTree K3)
{
	K3->Right = SingleRoatingLeft(K3->Right);  //右左旋转就是先左再右单次旋转。
	return SingleRoatingRight(K3);
}

//插入函数。
AVLTree
Insert(ElementType X, AVLTree T)
{
	if (T == NULL)
	{
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		if (T == NULL)
			FatalError("Out of space!!!");
		else
		{                                  //如果直接是一个空树，那么申请空间建树就行了。
			T->Height = 0;
			T->Left = T->Right = NULL;
			T->Data = X;
		}	
	}
	else
	{
		if (X < T->Data)
		{
			T->Left = Insert(X, T->Left);                       //这步一定要理解好。递归进行。当高度差小于2的时候，下面的不执行。
			if (GetHeigth(T->Left) - GetHeigth(T->Right) == 2)  //也就是递归到最后的NULL，然后从最后开始向上计算高度差
				if (X < T->Left->Data)                          //找到第一个高度差为2的，也就是受害者了，然后对受害者及其子树进行
					T = SingleRoatingLeft(T);                   //单次或者双次旋转，之后受害者变好了之后，再向上检查，这个时候
				else if (X > T->Left->Data)                     //上面的高度差也会一直小于2，也就是说这段代码再次不起作用
					T = DoubleRoatingLeft(T);                   //再就是到最后的根节点，之前随着向上各个节点的高度也在不断更新
		}                                                       //在最后就是将根节点的高度更新并且返回根节点即整棵树。
		else if (X > T->Data)
		{
			T->Right = Insert(X, T->Right);
			if (GetHeigth(T->Right) - GetHeigth(T->Left) == 2)
				if (X < T->Right->Data)
					T = DoubleRoatingRight(T);
				else if (X > T->Right->Data)
					T = SingleRoatingRight(T);
		}		
	}
	T->Height = Max(GetHeigth(T->Left), GetHeigth(T->Right)) + 1;

	return T;
}
