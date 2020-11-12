void
PolyPrint(Polynomial P)
{
	int flag = 0;

	if (!P)                  //如果上来就是空的，则输出0，0。
	{
		printf ("0,0\n");
		return;
	}
	while (P)               //遍历输出系数和指数。注意flag的用法，保证每一个节点之间存在一个空格。
	{                       //5 4 空格 4 3 空格 6 2……，也可以看成每一项前面带一个空格，除了第一项不带空格之外。
		if (flag == 0)
			flag = 1;
		else
			printf(" ");
		printf("%d %d", P->coef, P->expo);
		P = P->Next;
	}
	printf("\n");
}
