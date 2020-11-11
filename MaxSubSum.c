int MaxSubSum1 (int A[], int N)
{
	int i, j, k;
	int ThisSum, MaxSum;            //ThisSum代表的是当前循环的子序和，MaxSum代表整个的最大子序和。
	MaxSum = 0;
	for (i = 0; i < N; i++)         //第一层遍历，以便确定自序的起点。
	{
		for (j = i; j < N; j++)     //第二层遍历，确定子序的最大终点。
		{
			ThisSum = 0;
			for (k = i; k < j; k++)
			{
				ThisSum += A[k];

				if (ThisSum > MaxSum) //如果当前的子序和大于最大子序和，则对其进行更新。
					MaxSum = ThisSum;
			}
			
		}
	}

	return MaxSum;
}


int MaxSubSum2 (int A[], int N)
{
	int i, j;
	int MaxSum, ThisSum;
	MaxSum = 0;
	for (i = 0; i < N; i++)
	{
		ThisSum = 0;
		for (j = i; j < N; j++)
		{
			ThisSum += A[j];

			if (ThisSum > MaxSum)
				MaxSum = ThisSum;
		}
	}
	return MaxSum;
}

int MaxSubSum3(int A[], int N)
{
	int MaxSum1(int A[], int left, int right);
	return MaxSum1(A, 0, N - 1);
}
int MaxSum1(int A[], int left, int right)
{

	int center, MaxSum, MaxLeft, MaxRight, MaxMixLeft, MaxMixRight,ThisSum;
	int i, j;

	if (left == right)        //递归的出口，当左边和右边相等时。
		if (A[left] > 0)      //这个题目的要求是如果比0大，则返回值，如果比0小，则返回0。
			return A[left];
		else
			return 0;

	MaxSum = 0;
	center = (left + right) / 2;
	MaxLeft = MaxSum1(A, left, center);   //递归求左边部分的最大的子序和。
	MaxRight = MaxSum1(A, center + 1, right); //递归求出右边部分的最大子序和。

	MaxMixLeft = 0;                    //从中间开始，向左靠拢，得到和中间相连的左边的最大的子序和。
	for (i = center; i >= left; i--)
	{
		ThisSum = 0;
		ThisSum += A[i];

		if (ThisSum > MaxMixLeft)
			MaxMixLeft = ThisSum;
	}
	MaxMixRight = 0;                   //从中间开始，向左靠拢，得到和中间相连的左边的最大的子序和。
	for (j = center + 1; j <= right; j++)
	{
		ThisSum = 0;
		ThisSum += A[j];

		if (ThisSum > MaxMixRight)
			MaxMixRight = ThisSum;
	}
	//最大值只有三种情况，第一种是左边的最大值，第二种是右边的最大值，第三种是横跨左边右边连在一起的最大值。
	//这个题目的解题思路即是从这里出发，然后去找三种最大值是怎么进行求解。
	return Max3(MaxLeft, MaxRight, MaxMixLeft + MaxMixRight); 
}

int MaxSubSum4(int A[], int N)
{
	int i;
	int MaxSum,ThisSum;

	MaxSum = 0;
	for (i = 0; i < N; i++)
	{
		ThisSum = 0;
		ThisSum += A[i];

		if (ThisSum > MaxSum)     //当大于最大值时，更新最大值。
			MaxSum = ThisSum;
		else if (ThisSum < 0)     //当小于0时，代表如果增加这些子序列，将带来负面因影响。
			ThisSum = 0;          //题目要求如果最后为正则输出值，如果最后为负值，则输出0。
	}

	return MaxSum;
}
