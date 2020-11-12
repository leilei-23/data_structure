//两个多项式相乘
#include <stdio.h>                //引入这个头文件的原因是如果不引入的话下面的NULL会报错。
typedef struct Node* ptrtoNode;
typedef ptrtoNode Polynomial;

struct Node
{
	int coef;              //系数
	int expo;              //指数
	Polynomial Next;       //指向下一个节点的指针
};

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

Polynomial
PolyMux(Polynomial P1, Polynomial P2)
{
	Polynomial rear, font, t1, t2,Temp,P;
	int sume, sumc;

	if (!P1 || !P2)
		return NULL;

	rear = (Polynomial)malloc(sizeof(struct Node));
	font = rear;                          //还是两个指针，一个指向开始，一个指向结尾，用于插入新的节点。
	if (rear == NULL)
		FatalError("Out of space!!!");
	t1 = P1;                              
	t2 = P2;
	while (t2)
	{                //先用第一个多项式和第二个多项式每一项相乘，插入空链表中。
		Attach(t1->coef * t2->coef, t1->expo + t2->expo, &rear);    
		t2 = t2->Next;
	}
	while (t1)
	{                //然后开始遍历，用t1的每一项乘以t2，然后插入已知链表中。
		t2 = P2;  
		rear = font;
		while (t2)
		{
			sume = t1->expo + t2->expo;
			while (rear->Next->expo > sume && rear->Next)//当当前的指针的后一项的系数大的时候，指针后移，最后指针将停留在最后一个比
				rear = rear->Next;                       //系数大的位置，这个时候插入的位置就在当前位置的后面。
			if (rear->Next->expo = sume && rear->Next)   //注意需要考虑当前位置是否存在后一项，才能判断其系数之间的关系。
			{
				Temp = rear->Next;
				Temp->coef += t1->coef * t2->coef;
				if (!Temp->coef)                        //当相加为0，就要删除当前节点。
				{
					rear->Next = Temp->Next;
					free(Temp);                           //注意养成及时释放内存空间的好习惯。
				}
			}
			else
			{
				P = (Polynomial)malloc(sizeof(struct Node));
				if (P == NULL)
					FatalError("Out of space!!!");
				P->coef = t1->coef * t2->coef;
				P->expo = sume;                            //如果插入节点比当前节点之后的节点系数大，那直接插入即可。
				P->Next = rear->Next;
				rear->Next = P;
				rear = rear->Next;                         //个人认为这一步可有可无。即把指针后移，不后移则把这个再比较一遍
			}                                              //当然最好的情况是进行后移。
			t2 = t2->Next;
		}
		t1 = t1->Next;
	}

	t2 = font;
	font = font->Next;
	free(t2);

	return font;
}
