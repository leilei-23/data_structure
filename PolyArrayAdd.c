#define Maxdegreen 1000
struct Poly
{
	int coef[Maxdegreen + 1];       //Maxdegreen 是一个度，创建它的作用是为了方便运算。coef数组是记录多项式每一项的系数。
	int Highsize;                   //记录多项式的最高次数，这样每次就倒着进行运算就行了，不用每次都运算到Maxdegreen。
};

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
AddPloy(Polynomail P1, Polynomail P2, Polynomail P)
{
	int i;

	Zero(P);
	P->Highsize = P1->Highsize > P2->Highsize ? P1->Highsize : P2->Highsize;   //三元运算符求两个多项式最高系数较大者
	for (i = P->Highsize; i >= 0; i--)                                         //将运算局限在最高次数之内，倒序进行。
		P->coef[i] = P1->coef[i] + P2->coef[i];
}
