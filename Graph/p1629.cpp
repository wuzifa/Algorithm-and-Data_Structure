#ifdef RUN_P1629
#include <queue>
#include <vector>
#include <iostream>
#include <functional>
using namespace std;

//这道题主要学到的是怎么求解一个图中每个点到起点的最短路(边反向)，以及仔细梳理dijkstra算法

// dijkstra算法思路：
// 建立一个优先队列，循环，当队列不空，每次选取distance最小的点"u"对与它的出边相连的点"v"进行relaxation，relax过后记得pop出这个点，在relax的过程中如果有已经relax过的点就跳过
// relaxation: if(distance[u] + edge_cost(u, v) < distance[v]
//					distance[v] = distance[u] + edge_cost(u, v)
// 并且把成功将distance更新得更小的点入队，在选取distance最小的点时还要和distance数组作比较(记录当前每个点最小distance的数组)，
// 如果和distance数组相比优先队列里面的distance大于distance数组中记录，那就只作让它出队，因为这意味着前面这个点已经固定最小distance了，不需要再对它作一遍上述操作
//（这步叫懒惰删除，前面如果一个点的distance已经在队列中但是在relax别的点的过程中发现比当前这个在队列中的点的distance更小的distance时不会删除队列中的这个distance，因为删除的代价太大了）

struct node_info
{
	int m_index;
	int m_distance;
	node_info(int index, int distance)
		: m_index(index), m_distance(distance) {}
	//！！！注意std::priority_queue的大于小于应该理解的方式是优先级大于小于，默认谓词是less，想实现
	//值更小的优先级更大
	//priority_queue在比较时会把两边元素当成const来比较，记得将成员函数operator<加上const修饰符告诉priority_queue
	//自定义的operator<不会修改变量
	bool operator<(const node_info& other) const
	{
		//优先级小(位置靠尾)说明值更大
		return this->m_distance > other.m_distance;
	}
};


// 题目整体思路：
// 邮递员要给途中每个点送信并且返回至起点
// 所以要求起点到每个点的最短距离(1)和每个点到起点的最短距离(2)，答案 = Σ（ (1) + (2) ）= Σ(1) + Σ(2)
// 求(1)就是正常的dijkstra算法
// 求(2)的方法是把图中每条边反向，然后再求起点到每个点的最短距离
// 因为反向后 "原先图中每个点A返回起点的所有路" 就变成 "起点到这个点A的路"
// "求解每个点返回起点的最短路" 就转化成求 "起点到每个点的最短路"
// 这就变成正常dijkstra算法了
// 所以整体思路就是原图用一遍dijkstra算法，求出Σ(1)，所有边反向后再用一遍dijkstra算法，求出Σ(2)
int main()
{
	int node_num, edge_num;
	cin >> node_num >> edge_num;
	vector<int> distance(node_num + 1, INT_MAX);
	//vector<int> distance_back(node_num + 1, 0);
	vector<bool> relaxed(node_num + 1, false);
	//first: 点的index，second: 点的edge_cost
	vector<vector<pair<int, int>>> go_edgecost(node_num + 1);
	vector<vector<pair<int, int>>> back_edgecost(node_num + 1);
	int a, b, time;
	while (edge_num--)
	{
		cin >> a >> b >> time;
		go_edgecost[a].emplace_back(b, time);
		back_edgecost[b].emplace_back(a, time);
	}
	priority_queue<node_info> node;
	node.emplace(1, 0);
	// 这句千万不要漏了，因为distance[1]在第一次relax时不会被更新，
	// 而第一次relax过后index == 1的点就被设置为已经relax过的状态，如果下面这句不加distance[1]永远是INT_MAX
	distance[1] = 0;
	while (!node.empty())
	{
		int index = node.top().m_index;
		if (distance[index] < node.top().m_distance)
		{
			node.pop();
			continue;
		}
		for (auto tobe_relaxed : go_edgecost[index])
		{
			if (relaxed[tobe_relaxed.first])
				continue;
			if (distance[tobe_relaxed.first] > distance[index] + tobe_relaxed.second)
			{
				distance[tobe_relaxed.first] = distance[index] + tobe_relaxed.second;
				node.emplace(tobe_relaxed.first, distance[tobe_relaxed.first]);
			}
		}
		node.pop();
		relaxed[index] = true;
	}
	int total_cost = 0;
	for (int i = 2; i <= node_num; i++)
		total_cost += distance[i];

//=============================================================

	distance = std::move(vector<int>(node_num + 1, INT_MAX));
	relaxed = std::move(vector<bool>(node_num + 1, false));
	node.emplace(1, 0);
	distance[1] = 0;
	while (!node.empty())
	{
		int index = node.top().m_index;
		if (distance[index] < node.top().m_distance)
		{
			node.pop();
			continue;
		}
		for (auto tobe_relaxed : back_edgecost[index])
		{
			if (relaxed[tobe_relaxed.first])
				continue;
			if (distance[tobe_relaxed.first] > distance[index] + tobe_relaxed.second)
			{
				distance[tobe_relaxed.first] = distance[index] + tobe_relaxed.second;
				node.emplace(tobe_relaxed.first, distance[tobe_relaxed.first]);
			}
		}
		node.pop();
		relaxed[index] = true;
	}
	for (int i = 2; i <= node_num; i++)
		total_cost += distance[i];
	cout << total_cost << endl;
}

#endif