#ifdef RUN_P1968
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

//子问题：在第i天美元的最大值
//前提子问题：第i - 1天如果持有的是美元，第i - 1天美元的最大值
//          第i - 1天如果持有的是马克，马克的最大值
//          因为不知道第i天的汇率，所以两个币种在第i - 1天的最大值都需要知道
//          上面既然在求第i天美元的最大值需要第i - 1天马克的最大值，所以子问题又多了第i天马克的最大值
//          求解第i天马克的最大值的思路和求第i天美元最大值的思路一样
int main()
{
	//dp[0][i]表示第i天可以取得的美元的最大值，dp[1][i]表示第i天可以取得的马克的最大值，
	double dp[2][102];
	short days;
	cin >> days;
	dp[0][0] = 100.0;
	dp[1][0] = 0.0;
	double rate_mark;
	for (int i = 1; i <= days; i++)
	{
		cin >> rate_mark;
		dp[0][i] = max(dp[0][i - 1], dp[1][i - 1] / rate_mark * 100.0);
		dp[1][i] = max(dp[1][i - 1], dp[0][i - 1] / 100.0 * rate_mark);
	}
	cout << fixed << setprecision(2) << dp[0][days] << endl;
}
#endif