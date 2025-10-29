#ifdef RUN_P1115
//kadane算法
#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
	int now_optimal_solution = -1, global_optimal_solution = (int)-1e5;
	unsigned data_num;
	vector<int> data;
	cin >> data_num;
	data.resize(data_num);
	for (unsigned int i = 0; i < data_num; i++)
	{
		cin >> data[i];
	}
	for (int i : data)
	{
		if (now_optimal_solution < 0)
			now_optimal_solution = i;
		else
			now_optimal_solution += i;
		if (now_optimal_solution > global_optimal_solution)
			global_optimal_solution = now_optimal_solution;
	}
	cout << global_optimal_solution << endl;
}
//关键步骤：
//now_optimal_solution = max(data[i], now_optimal_solution + data[i]);
//global_optimal_solution = max(global_optimal_solution, now_optimal_solution);
// 
//dp递推式：dp[i]=max(data[i],dp[i−1]+data[i])
//然后取所有 dp[i] 中的最大值作为答案
//kadane算法每次在做：
//在当前位置 i，判断：
//是更好地 延续 前面的子段（now_optimal_solution + data[i]），
//还是 重新开始一个新的子段（只取 data[i]），所以变向来说kadane算法尝试了所有子段
//每次只有两个操作：延续当前子段或者结束当前子段，不可以当新元素为负时我不取，然后取后面为正的，这样不连续
//所以可能好不容易累加起来的正子段可能因为几个负数而不得不终结，这是因为问题要求连续而没办法的

#endif