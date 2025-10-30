#ifdef RUN_P1144
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <list>
#include <deque>
#include <chrono>
using namespace std;


//struct Timer//计时器，在构造时开始计时，析构时结束计时
//{
//	std::chrono::time_point<std::chrono::steady_clock> start, end;
//	std::chrono::duration<float> duration;
//
//	Timer() :
//		start(std::chrono::high_resolution_clock::now()) {
//	}
//
//	~Timer()
//	{
//		end = std::chrono::high_resolution_clock::now();
//		duration = end - start;
//
//		float ms = duration.count() * 1000.0f;
//		cout << "Timer took " << ms << " ms" << endl;
//	}
//};


int main(void)
{
	//和C的输入输出解绑，这样提高输入输出速度，但是不能再用c风格输入输出
	ios::sync_with_stdio(false);
	//原本每次cin前会确保cout内容已经输出，现在不再管cout，提高输入速度
	cin.tie(nullptr);
#ifndef ONLINE_JUDGE
	freopen("C:/Users/wuzif/source/repos/everyday_homework/testdata/P1144_6.in", "r", stdin);
	freopen("C:/Users/wuzif/source/repos/everyday_homework/testdata/P1144_6.out", "w", stdout);
#endif
	vector<unsigned int> road_num;
	vector<vector<unsigned int>> adj;
	unsigned int node_num, edge_num, a, b;
	cin >> node_num >> edge_num;
	vector<bool> visited;
	adj.resize(node_num + 1, vector<unsigned int>(4, 0));
	road_num.resize(node_num + 1, 0);
	visited.resize(node_num + 1, false);
	while (edge_num--)
	{
		cin >> a >> b;
		adj[a].emplace_back(b);
		
		adj[b].emplace_back(a);
		
	}
	deque<unsigned int> node_queue;
	node_queue.push_back(1);
	road_num[1] = 1;
	unsigned int vertex_pushed_in_deque;
	
	unsigned int now_exploring;
	unsigned int thisround_willbe_pushed = 1;
	visited[1] = true;
	vector<unsigned int> pushednode;
	while (!node_queue.empty())
	{
		pushednode.clear();
		vertex_pushed_in_deque = thisround_willbe_pushed;
		thisround_willbe_pushed = 0;
		while (vertex_pushed_in_deque--)
		{
			now_exploring = node_queue.front();
			node_queue.pop_front();
			
			for (auto tobeadded : adj[now_exploring])//O(M)
			{
				if (!visited[tobeadded])
				{
					if (road_num[tobeadded] == 0)
					{
						node_queue.push_back(tobeadded);
						thisround_willbe_pushed++;
						pushednode.push_back(tobeadded);
					}
					road_num[tobeadded] = (road_num[now_exploring] + road_num[tobeadded]) % 100003;
				}
			}
		}
		for (unsigned visitednode : pushednode)//O(N)
		{
			visited[visitednode] = true;
		}
	}
	for (auto it = road_num.begin() + 1; it != road_num.end(); it++)
	{
		cout << *it % 100003 << '\n';
	}
	return 0;
}


#endif
//我这个逻辑不能在入队时立即标记 visited，如果一个节点a到另一个节点b有多重边，那么在访问节点a的邻接表时候后面的多重边节点就计数记不到了，并且我的pushednode数组就是为了预防多重边太多导致的遍历重复太多导致超时，而且nodequeue在节点入队后这个节点对应的road_num就不为0了，不会将重边导致的节点重复入队
//所以超时的原因我觉得不是你说的，超内存可能是因为重边太多导致数组过大