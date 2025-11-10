#ifdef RUN_P2842
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// 建立dp表,每个位置表示凑出这个位置的金额所需的最小硬币数(子问题)
// dp[i] = min{ 1 + dp[i - cashⁱ] }(cashⁱ < i)			子问题间关系，每一步尝试所有可能，取最优解
int main()
{
	int cash_kind, total_num;
	cin >> cash_kind >> total_num;
	vector<int> cash(cash_kind, 0);
	for (int i = 0; i < cash_kind; i++)
	{
		cin >> cash[i];
	}
	vector<int> dp(total_num + 1, 0);
	dp[0] = 0;
	for (int i = 1; i <= total_num; i++)
	{
		int min_num = INT_MAX;
		for (int j : cash)
		{
			//后面这句dp[i - j] != INT_MAX一定要加上，可能出现某一个dp[i]因为
			//所有面额都大于i而导致这个dp[i]为INT_MAX 或者 在尝试了所有的cash后所有的子状态都是INT_MAX(凑不出这样的金额)
			//动态规划不仅会把最优解进行传递，还会把"无效状态"进行传递，如果部分子状态是无效状态(凑不出这样的金额)，那下面的机制就会自然跳过这样的情况
			//只选取在符合"现实情况下"的最优效子状态
			//如果所有子状态都是无效状态，那当前状态也是无效状态
			if (j <= i && dp[i - j] != INT_MAX)
				min_num = min(min_num, 1 + dp[i - j]);
		}
		dp[i] = min_num;
	}
	if (dp[total_num] != INT_MAX)
		cout << dp[total_num] << endl;
	else
		cout << "凑不出" << endl;
}

#endif