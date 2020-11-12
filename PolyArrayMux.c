typedef struct Poly* Polynomail;

//构建清零函数。
void
Zero(Polynomail P)
{
	int i;

	for (i = 0; i <= Maxdegreen; i++)     //将系数数组进行清零。
		P->coef[i] = 0;
	P->Highsize = 0;                     //将多项式最高次数进行清零。
}

//构建多项式相加函数
void
MuxPloy(Polynomail P1, Polynomail P2, Polynomail P)
{
	int i, j;

	Zero(P);
	P->Highsize = P1->Highsize + P2->Highsize;   //两个多项式最高系数相加即为新多项式的最高系数。
	if (P->Highsize > Maxdegreen)
		Error("Exceeded array size!!!");         //这里要注意检验是否超过了那个度。
	else
	{
		for (i = 0; i <= P1->Highsize; i++)
			for (j = 0; j <= P2->Highsize; j++)
				P->coef[i + j] += P1->coef[i] * P2->coef[i];
	}
}
