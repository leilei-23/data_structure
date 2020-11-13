#include <stdio.h>
typedef int ElementType;
typedef struct TreeNode* SerchTree;   //学会使用这种两种名称的方式，因为一种是指向这棵树的最开始的树节点，代表整棵树。
typedef struct TreeNode* Position;    //另一个代表这棵树上任意位置的树节点，并不是代表整棵树，但是他们都是指向树结点的指针。

struct TreeNode
{
	ElementType Data;
	SerchTree Left;
	SerchTree Right;
};

//清空树的函数。
SerchTree
MakeEmpty(SerchTree T)
{
	if (T != NULL)       //如果树不是空的，那么就把他的左子树和右子树都清空。
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

//查找函数。
Position
Find(ElementType X, SerchTree T)
{
	if (T == NULL)             //一定要记得考虑边界条件，即树为空的条件。
		return NULL;
	if (X < T->Data)
		return Find(X, T->Left);
	else if (X > T->Data)
		return Find(X, T->Right);  //这里注意return的使用！
	else
		return T;
}

//查找最小值的函数。用递归形式实现。
Position
FindMin(SerchTree T)
{
	if (T == NULL)
		return NULL;
	else
	{
		if (T->Left == NULL)
			return T;
		else
			return FindMin(T->Left);		
	}
}

//查找最大值的函数，用while形式实现。
Position
FindMax(SerchTree T)
{
	if (T != NULL)
		while (T->Right != NULL)
			T = T->Right;
	return T;
}

//插入函数。
SerchTree
Insert(ElementType X, SerchTree T)
{
	if (T == NULL)     //还是对树是空的情况的讨论。
	{
		T = (SerchTree)malloc(sizeof(struct TreeNode));
		if (T == NULL)
			FatalError("Out of space!!!");
		else
		{
			T->Data = X;
			T->Left = T->Right = NULL;
		}
	}
	else
	{
		if (X < T->Data)
			T->Left = Insert(X, T->Left);    //注意调用函数时的返回值。
		else if (X > T->Data)
			T->Right = Insert(X, T->Right);
	}
	return T;
}

//删除函数
SerchTree
Delete(ElementType X, SerchTree T)
{
	if (T == NULL)
		Error("Empty Tree!!!");
	if (X < T->Data)
		T->Left = Delete(X, T->Left);
	else if (X > T->Data)
		T->Right = Delete(X, T->Right);     //调用函数时的返回值！
	else
	{
		if (T->Left && T->Right)
		{
			Position Temp;

			Temp = FindMin(T->Right);
			T->Data = Temp->Data;
			T->Right = Delete(T->Data, T->Right); //调用函数时的返回值。
		}
		else
		{
			SerchTree temp;

			temp = T;
			if (T->Left == NULL)
				T = T->Right;
			else if (T->Right == NULL)
				T = T->Left;
			free(temp);
		}
	}
	return T;
}
