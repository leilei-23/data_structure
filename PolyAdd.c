//多项式相加函数
#include <stdio.h>                //引入这个头文件的原因是如果不引入的话下面的NULL会报错。
typedef struct Node* ptrtoNode;
typedef ptrtoNode Polynomial;

struct Node
{
	int coef;              //系数
	int expo;              //指数
	Polynomial Next;       //指向下一个节点的指针
};

Polynomial
PolyAdd(Polynomial P1, Polynomial P2)
{
	void Attach(int c, int e, Polynomial * Ptrear);   //函数声明。

	Polynomial rear, font, temp;
	int sumc;

	rear = (Polynomial)malloc(sizeof(struct Node));
	if (rear == NULL)                               //向系统申请空间的时候一定要学会加上这个东西。
		FatalError("Out of space!!!");
	font = rear;                        //这里创建了一个空链表，并定义两个指针，一个用于记录头结点，以便于对最后的链表进行输出
	                                    // 另一个用于记录尾节点，随着多项式节点的不断插入，尾节点不断向后移动。               
	while (!P1 && !P2)                  //如果P1和P2中有一个已经到最后了，则停止这个循环，把剩下的追加到后面。
	{
		if (P1->expo > P2->expo)                     
		{
			Attach(P1->coef, P1->expo, &rear);
			P1 = P1->Next;
			break;
		}
		else if (P1->expo < P2->expo)
		{
			Attach(P2->coef, P2->expo, &rear);
			P2 = P2->Next;
			break;
		}
		else
		{
			sumc = P1->coef + P2->coef;
			if (sumc)                              //讨论相加之后是否为0。
			{
				Attach(sumc, P1->expo, &rear);
				P1 = P1->Next;
				P2 = P2->Next;
				break;
			}
		}
	}
	for (; P1; P1 = P1->Next)
		Attach(P1->coef, P1->expo, &rear);
	for (; P2; P2 = P2->Next)
		Attach(P2->coef, P2->expo, &rear);
	rear->Next = NULL;                           //给最后的指针指向NULL。

	temp = font;
	font = font->Next;
	free(temp);

	return font;
}

void Attach(int c, int e, Polynomial* Ptrear)   //这里是跨函数对rear进行修改，所以要用地址，即指向指针的指针。
{
	Polynomial P;

	P = (Polynomial)malloc(sizeof(struct Node));
	if (P == NULL)
		FatalError("Out of space!!!");

	P->coef = c;
	P->expo = e;
	P->Next = NULL;                        //创建一个新指针记录系数以及指数
	(*Ptrear)->Next = P;                 
	(*Ptrear) = P;                        //P向后挪一个。
}
