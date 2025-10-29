#ifdef RUN_P1719
#include <iostream>
using namespace std;

inline int max(int a, int b)
{
	return a > b ? a : b;
}

//最大字段和算法
int Kadane(int* arr, int num)
{
	int current_sum, max_sum;
	for (int i = 0; i < num; i++)
	{
		if (i == 0)
			current_sum = max_sum = arr[0];
		else
		{
			current_sum = max(current_sum + arr[i], arr[i]);
			max_sum = max(max_sum, current_sum);
		}
	}
	return max_sum;
}

int main(void)
{
	int n, ans, band_max;
	cin >> n;
	//因为矩阵抵消在运行时才确定，所以在堆上分配内存
	int* const column_sum = new int[n];//用来存储top和bottom确定后的列和
	int** matrix = new int*[n];//模拟二维数组
	for(int i = 0; i < n; i++)
	{
		matrix[i] = new int[n];
	}
	for(int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> matrix[i][j];
		}
	}
	ans = matrix[0][0];//初始化ans为矩阵中单个元素，注意不可初始化为0，防止矩阵全负
	for(int top = 0; top < n; top++)//top:0 -> n - 1, O(n)
	{
		for (int i = 0; i < n; i++)
		{
			column_sum[i] = 0;
		}
		for (int bottom = top; bottom < n; bottom++)//bottom: top -> n - 1, O(n)
		{
			for (int j = 0; j < n; j++)//O(n)
			{
				column_sum[j] += matrix[bottom][j];/*每次bottom更新时更新列和，即增量累加法，不要从头开始算
			列和，因为从头开始算要遍历行，为O(n),此时最高时间复杂度为O(n4次方)*/
			}
			band_max = Kadane(column_sum, n);//在column_sum数组上运行Kadane，得到 bandMax（该 top-bottom 带的最大子阵）
			ans = max(ans, band_max);//若有更大的band_max，则更新answer
		}
	}
	cout << ans << endl;
}
#endif