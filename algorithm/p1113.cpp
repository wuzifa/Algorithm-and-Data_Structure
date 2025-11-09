#ifdef RUN_P1113
#include <iostream>
#include <vector>
using namespace std;
vector<int> cost;//记忆化
vector<short> chore_time;//记录题目输入以及在动态规划时的算法要用
vector<vector<short>> prev_chore;//帮助组织动态规划算法

// 这个题目子问题和子问题之间的关系很明确了
// 完成一个杂物至少需要的时间是完成所有前置必须杂物至少所需时间的最大值加上完成当前杂物所需时间，因为状态转移的方向不是很明确 / 固定，所以用递归，不用tabulation / recursion
// 又因为在递归的时候可能会对一个杂物反复求完成它至少所需时间，所以又要加记忆化
// 个人感觉应该从所需前置杂物少的杂物开始向所需前置杂物多的递归，这样能体现从小问题向大问题过渡

// 具体思路: 
// 遍历图图上每个节点，求完成这个点代表的杂务至少需要的时间，求出来后记录到数组里，
// 然后遍历完图上每个点后求每个杂务所需时间最大的 
// 在求完成每个杂务至少需要的时间时采用递归方法，求它完成它前面必须完成的杂务中所需时间最多的，加上它自己所需的时间

//原来的思路(贪心)不对(见提交记录)，因为题目的输入并不能确保图的阶段性是很明确的，在取next_chore最大的时，可能取到了跳了很多杂务的点

//状态转移公式: cost(i) = max{cost(j)} + chore_time(i) j为完成i的前提杂务

static int findcost(int no)
{
	//查询记忆化表
	if (cost[no] != 0)
		return cost[no];
	else
	{
		int max_time = -1, new_time;
		//针对每个前提杂务进行递归
		for (int i : prev_chore[no])
		{
			new_time = findcost(i);
			if (max_time < findcost(i))
				max_time = new_time;
		}
		//将结果记录到记忆化表中，方便下次递归到这个点时不用重复计算
		cost[no] = max_time + chore_time[no];
		return cost[no];
	}
}

int main()
{
	int chore_num;
	cin >> chore_num;
	cost = std::move(vector<int>(chore_num + 1, 0));
	chore_time = std::move(vector<short>(chore_num + 1, 0));
	prev_chore = std::move(vector<vector<short>>(chore_num + 1));
	int chore_no, time, prev;
	for(int i = 0; i < chore_num; i++)
	{
		cin >> chore_no >> time;
		chore_time[chore_no] = time;
		while (true)
		{
			cin >> prev;
			if (prev == 0)
				break;
			prev_chore[chore_no].push_back(prev);
		}
	}
	cost[1] = chore_time[1];
	int max_cost = -1;
	for (int i = 1; i <= chore_num; i++)
	{
		int newcost = findcost(i);
		if (max_cost < newcost)
			max_cost = newcost;
	}
	cout << max_cost << endl;
}


#endif