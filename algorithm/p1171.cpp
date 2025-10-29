#ifdef RUN_P1171
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;





//显示这个subset(每个元素在subset中是否存在)
template<typename T, typename func>
void loop_mask(T subset, int ele_num, func f, int larger_mask)
{
	//遍历每个bit查看它是否为0
	for (int bit_no = 0; bit_no < ele_num; bit_no++)
	{
		if (subset & (T(1) << bit_no))
		{
			f();
		}
	}
	cout << endl;//后面实现真正相关逻辑时把这里删了
}

template<typename T>
void remove(T& subset, int index)
//index从0开始
{
	if (index < sizeof(T) * 8)
	{
		if (subset & (T(1) << index))
			subset ^= (T(1) << index);
	}
}

template<typename T>
void add(T& subset, int index)
//index从0开始
{
	if (index < sizeof(T) * 8)
	{
		if (!(subset & (T(1) << index)))
			subset ^= (T(1) << index);
	}
}

//设置好一个mask需要mask上有total_bit个at标记(设置过1),每后面一层递归只能在前面一层的at的后面尝试标记at
template<typename T>
void mask_producer(T& set, int at, int tobe_produced, int total_bit, vector<T>& mask_set)
{ 
	//当没有1需要继续被设置时，说明找到了一个符合要求的mask，不用再继续递归
	//直接回溯
	if (tobe_produced == 0)
	{
		mask_set.push_back(set);
	}
	//当还有1需要继续被设置时
	else
	{
		//在这一层递归需要对当前传进来的at代表的数以及后面的数都试一遍标记at
		for (int i = at; i < total_bit; i++)
		{
			
			//如果后面可以设置1的空间不足，则不进入递归
			if (total_bit - i >= tobe_produced - 1)
			{
				set ^= (T(1) << i);
				mask_producer(set, i + 1, tobe_produced - 1, total_bit, mask_set);
				//在尝试当前递归层的下一个选择是要先把当前尝试的痕迹去除
				set ^= (T(1) << i);
			}
		}
	}
}

template <typename T>
bool inmask(int index, T data)
//index从零开始！！
{
	return data & (T(1) << index);
}
//============上面实现bitmask表示子集===========
//
//
//dp(i, set) = min{c(i, k) + dp(k, set - k)}, k为set中一个点

//子问题为dp[j][mask],表示从起点出发visit完mask表示的子集并且以j节点作为结尾的最短路径
//子问题有两个维度:一个是已经visit过的节点的数量，另一个是已经已经visit过的节点集中谁是重点，这是引导写下面dp算法的核心，很重要！！！
//子问题与子问题之间关系:
//
// 
// 
// 
//解决tsp问题的dp算法框架
// 
//1.初始化dp表的大小:Double[][] memo = new Double[N][1 << N]
//这样建立是因为每个mask子集都有N个节点作为最后节点的可能(在不知道起始节点的情况下)
//但是在实际运行中因为对于一些mask有些节点一定不可能作为最后节点因为有些节点不在mask表示的子集内，
//所以这个dp表有些地方是空的-->Bitmask DP 的稀疏性本质,表格虽然是 N × (1 << N)，但有效状态数量其实远小于 N ×(1 << N)
// 
//2.初始化表格:memo[end][(1 << start) | (1 << end)] = distance[start][end](end != start)
//(1 << start) | (1 << end)通过按位或运算建立了包含start和end节点的子集
// 
//3.一步步扩展mask中已经visit过的节点的数量
//(下面只是循环的一轮，从visited == 3开始，要循环到mask中包含所有题目中的节点，然后再交给下面最后一步处理函数，将从0visit过所有节点并且以j节点作为终点的的最短路径连接回起点)
//for_each(larger_mask)，这里要写一个larger_mask生成器
//		检查起点是否包含在larger_mask中，因为拓展已visit过的节点的前提是起点在这个已visit过的节点集中
//		遍历larger_mask中每个节点N(除了起点)，将其作为larger_mask的终点
//				得到去掉上面这个larger_mask的终点的prev_mask
//				遍历这个mask中每个节点(除了起点)，将其作为prev_mask的终点M
//						寻找哪个点M作为终点时的dp加上edge_cost(M, N)最小，将其作为dp[N][larger_mask](状态转移,完成了对一个更大子问题的求解,同时这里也展示了子问题与子问题之间的关系)
//
//4.将上面得到的所有(dp[j][END_STATE](0 <= j < N) 加上 edge_cost(j, 起点))取最小值，得到答案
//
//5.得到路径具体是什么
//上面在dp表中每个元素只存了最短路径值，这里临时决定再加上一个prev在路径回溯时沿着prev找回去就行了,
//最后别忘了在路径顺序，找回去是如果是每次push_back那么在最后要将路径反转一下
//
//
//
// 
//
//

struct dp_info
{
	int optimal_distance;
	int last_node;
	dp_info()
		: optimal_distance(0), last_node(0) {}
};

int main(void)
{
	
	int village_num;
	cin >> village_num;
	vector<vector<int>> adj(village_num, vector<int>(village_num, 0));
	vector<vector<dp_info>> dp(village_num, vector<dp_info>(1 << village_num));
	int start = 0;
	for (int i = 0; i < village_num; i++)
	{
		for (int j = 0; j < village_num; j++)
		{
			cin >> adj[i][j];
		}
	}
	for (int i = 1; i < village_num; i++)
	{
		dp[i][1 << start | 1 << i].optimal_distance = adj[start][i];
		dp[i][1 << start | 1 << i].last_node = -1;
	}
	int mask_production = 0;
	vector<int> mask_container;
	for (int i = 3; i <= village_num; i++)
	{
		mask_container.clear();
		mask_production = 0;
		//创建大小为i的子问题集(已visit节点为i个)
		mask_producer<int>(mask_production, 0, i, village_num, mask_container);
		for (int larger_mask : mask_container)
		{
			//只留下从起点出发，visit了i个节点的子问题
			if (!inmask(start, larger_mask))
				continue;
			for (int end_point = 0; end_point < village_num; end_point++)
			{
				//下面相当于在遍历符合要求的子问题中包含的节点(除了起点)
				//从子问题集中选中某个具体的子问题
				if (end_point == start)
					continue;
				if (larger_mask & (1 << end_point))
				{
					int prev_mask = larger_mask;
					//得到前提子问题prev_mask
					remove<int>(prev_mask, end_point);
					int optimal_distance = INT_MAX;
					int best_index;
					//下面相当于遍历ziwenti1prev_mask中的节点(除了起点)
					for (int end_point_prev = 0; end_point_prev < village_num; end_point_prev++)
					{
						if ((prev_mask & (1 << end_point_prev)) && (end_point_prev != start))
						{
							int new_distance = adj[end_point_prev][end_point] + dp[end_point_prev][prev_mask].optimal_distance;
							//通过前提子问题求解当前子问题的最优解
							if (new_distance < optimal_distance)
							{
								optimal_distance = new_distance;
								best_index = end_point_prev;
							}
						}
					}
					//记录子问题最优解
					dp[end_point][larger_mask].optimal_distance = optimal_distance;
					dp[end_point][larger_mask].last_node = best_index;
				}
			}
		}
	}
	int end_state = (1 << village_num) - 1;
	int min_distance = INT_MAX;
	int last_min_index;
	int compare;
	for (int i = 0; i < village_num; i++)
	{
		if(i == start)
			continue;
		compare = dp[i][end_state].optimal_distance + adj[i][start];
		if (compare < min_distance)
		{
			min_distance = compare;
			last_min_index = i;
		}
	}
	cout << min_distance << endl;
	vector<int> optimal_path;
	optimal_path.push_back(start);
	int state = end_state, track = last_min_index;
	while (track != -1)
	{
		optimal_path.push_back(track);
		int temp = track;
		track = dp[track][state].last_node;
		remove(state, temp);
	}
	optimal_path.push_back(start);
	std::reverse(optimal_path.begin(), optimal_path.end());
	for (int i : optimal_path)
		cout << i << ' ';
	cout << endl;
	return 0;
}


#endif