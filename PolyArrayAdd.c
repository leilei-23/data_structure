#define Maxdegreen 1000
struct Poly
{
	int coef[Maxdegreen + 1];
	int Highsize;
};

typedef struct Poly* Polynomail;

//构建清零函数。
void
Zero(Polynomail P)
{
	int i;

	for (i = 0; i <= Maxdegreen; i++)
		P->coef[i] = 0;
	P->Highsize = 0;
}

//构建多项式相加函数
void
AddPloy(Polynomail P1, Polynomail P2, Polynomail P)
{
	int i;

	Zero(P);
	P->Highsize = P1->Highsize > P2->Highsize ? P1->Highsize : P2->Highsize;
	for (i = P->Highsize; i >= 0; i--)
		P->coef[i] = P1->coef[i] + P2->coef[i];
}
