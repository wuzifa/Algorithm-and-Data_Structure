#ifdef RUN_TEST
#include <iostream>
#include <vector>
using namespace std;


//以下为答案:

int gcd(int a, int b) 
{
	int remainder;
	while (b != 0)
	{
		remainder = a % b;
		a = b;
		b = remainder;
	}
	return a;
}

//--------------------------------------------------------------------------


int fibonacci(int k) 
{
	vector<int> F(k + 1, -1);
	if (F[k] != -1)
		return F[k];
	if (k <= 1)
	{
		F[k] = k;
		return k;
	}
	
	F[k] = fibonacci(k - 2) + fibonacci(k - 1);
	return F[k];
}

//-------------------------------------------------------------------------

int login(int accounts[], int passwords[], int size, int inputAccount, int inputPassword) 
{
	for (int i = 0; i < size; i++)
	{
		if (inputAccount == accounts[i])
		{
			if (inputPassword == passwords[i])
				return 1;
			return 0;
		}
	}
	return 0;
}

//------------------------------------------------------------------------

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void bubbleSort(int* arr, int size)
{
	int r_bound = size - 2;
	while (r_bound > 0)
	{
		for (int i = 0; i <= r_bound; i++)
		{
			if (arr[i] < arr[i + 1])
				swap(arr[i], arr[i + 1]);
		}
		r_bound--;
	}
}

int getKthLargest(int arr[], int size, int k) 
{
	bubbleSort(arr, size);
	return arr[k - 1];
}

//-------------------------------------------------------------------------

int isValidDate(int year, int month, int day) {
	if (day == 29)
	{
		if (month == 2)
		{
			if (year % 4 == 0)
			{
				if (!(year % 100 == 0 && year % 400 != 0))
					return 1;
			}
				
		}
	}
	else if (day == 31)
	{
		switch (month)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (year > 0)
				return 1;
		}
	}
	else
	{
		if (day > 0)
		{
			if (month > 0 && month < 13)
			{
				if (year > 0)
					return 1;
			}
		}
	}
	return 0;
}

//-------------------------------------------------------------------------



//以下为测试:


int main() {
	printf("测试gcd函数:\n");
	int gcd_test_cases[][3] = {
		{48, 18, 6},
		{7, 13, 1},
		{0, 5, 5},       // 边界情况:一个数字为零
		{12, 12, 12},    // 边界情况:相同数字
		{1071, 462, 21}, // 更大数字:1071和462
		{270, 192, 6}    // 附加测试用例
	};

	for (int i = 0; i < sizeof(gcd_test_cases) / sizeof(gcd_test_cases[0]); i++) {
		int result = gcd(gcd_test_cases[i][0], gcd_test_cases[i][1]);
		printf("gcd(%d, %d) = %d [%s]\n",
			gcd_test_cases[i][0], gcd_test_cases[i][1], result,
			result == gcd_test_cases[i][2] ? "通过" : "失败");
	}
	printf("\n");

	printf("测试fibonacci函数:\n");
	int fib_test_cases[][2] = {
		{1, 1},
		{2, 1},
		{5, 5},
		{10, 55},      // 第10个斐波那契数
		{15, 610},     // 第15个斐波那契数
		{20, 6765}     // 第20个斐波那契数
	};

	for (int i = 0; i < sizeof(fib_test_cases) / sizeof(fib_test_cases[0]); i++) {
		int result = fibonacci(fib_test_cases[i][0]);
		printf("fibonacci(%d) = %d [%s]\n",
			fib_test_cases[i][0], result,
			result == fib_test_cases[i][1] ? "通过" : "失败");
	}
	printf("\n");

	printf("测试getKthLargest函数:\n");
	int arr1[] = { 4, 2, 7, 1, 3, 9, 5, 8, 6 };
	int size1 = sizeof(arr1) / sizeof(arr1[0]);

	int kth_test_cases[][3] = {
		{1, 9},  // 第1大
		{2, 8},  // 第2大
		{5, 5},  // 第5大
		{9, 1}   // 第9大(最小)
	};

	for (int i = 0; i < sizeof(kth_test_cases) / sizeof(kth_test_cases[0]); i++) {
		int result = getKthLargest(arr1, size1, kth_test_cases[i][0]);
		printf("getKthLargest(arr1, %d, %d) = %d [%s]\n",
			size1, kth_test_cases[i][0], result,
			result == kth_test_cases[i][1] ? "通过" : "失败");
	}


	printf("测试login函数:\n");
	int accounts[10] = { 1001, 1002, 1003, 1004, 0, 0, 0, 0, 0, 0 };
	int passwords[10] = { 1234, 5678, 9012, 3456, 0, 0, 0, 0, 0, 0 };

	int login_test_cases[][4] = {
		{1001, 1234, 1},  // 正确
		{1002, 5678, 1},  // 正确
		{1001, 9999, 0},  // 错误密码
		{9999, 1234, 0},  // 不存在的账号
		{1003, 9012, 1},  // 正确
		{1004, 0000, 0}   // 错误密码
	};

	for (int i = 0; i < sizeof(login_test_cases) / sizeof(login_test_cases[0]); i++) {
		int result = login(accounts, passwords, 10, login_test_cases[i][0], login_test_cases[i][1]);
		printf("login(%d, %d) = %d [%s]\n",
			login_test_cases[i][0], login_test_cases[i][1], result,
			result == login_test_cases[i][2] ? "通过" : "失败");
	}
	printf("\n");

	printf("测试isValidDate函数:\n");
	// 日期验证测试用例
	int date_test_cases[][4] = {
		{2023, 2, 28, 1},  // 有效日期:平年2月28日
		{2020, 2, 29, 1},  // 有效日期:闰年2月29日
		{2000, 2, 29, 1},  // 有效日期:世纪闰年2月29日
		{2023, 2, 29, 0},  // 无效日期:平年2月29日
		{2023, 4, 31, 0},  // 无效日期:4月31日
		{2023, 13, 1, 0},  // 无效日期:13月
		{0, 1, 1, 0},      // 无效日期:0年
		{2023, 0, 1, 0},   // 无效日期:0月
		{2023, 1, 0, 0},   // 无效日期:0日
		{2023, 12, 31, 1}, // 有效日期:12月31日
		{2023, 11, 30, 1}, // 有效日期:11月30日
		{2023, 10, 31, 1}  // 有效日期:10月31日
	};

	for (int i = 0; i < sizeof(date_test_cases) / sizeof(date_test_cases[0]); i++) {
		int result = isValidDate(date_test_cases[i][0], date_test_cases[i][1], date_test_cases[i][2]);
		printf("isValidDate(%d, %d, %d) = %d [%s]\n",
			date_test_cases[i][0], date_test_cases[i][1], date_test_cases[i][2], result,
			result == date_test_cases[i][3] ? "通过" : "失败");
	}

	return 0;
}
#endif
