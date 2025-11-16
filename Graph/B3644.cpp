#ifdef RUN_B3644
#include <vector>
#include <iostream>
#include <deque>
#include <list>
using namespace std;
//需要的数据结构：
// 1.邻接表（存每个点的出边）
//
// 2.一个数组存每个点是否已经访问过
//
// 3.一个集合存还剩下哪些点没访问过
// 这个集合应满足的要求：
//		1.频繁将已经访问过的节点删除
//		2.每次一轮DFS完后需要随便选取一个该集合中的点
// 综上考虑选list，删除操作为O(n)，原本选的vector，vector删除后元素位置会改变，
// 如果下次还根据某个点的索引来删除这个点就会引发数组访问越界，所以不选vector
//
// 4.答案数组（存最终的排序结果）
//
static vector<vector<int>> adj_list;
static vector<bool> visited;
static list<int> notvisitedyet;
static deque<int> ans;

void topological_sort(int offspring)
{
	//遍历所有出边相连的点
	for (int i : adj_list[offspring])
	{
		//如果这个点还没访问过，则DFS递归下去
		if (!visited[i])
			topological_sort(i);
	}
	//这个点的所有出边的点访问完后将这个点push_front进答案序列
	ans.push_front(offspring);
	//同时意味着这个点访问过了
	visited[offspring] = true;
	//将这个点从存储未访问点的集合中移除
	notvisitedyet.remove(offspring);
}

int main()
{
	int people_num;
	cin >> people_num;
	adj_list.resize(people_num + 1);
	visited.resize(people_num + 1, false);
	int descendant;
	for (int i = 1; i <= people_num; i++)
	{
		notvisitedyet.push_back(i);
		while (true)
		{
			cin >> descendant;
			if (descendant == 0)
				break;
			adj_list[i].push_back(descendant);
		}
	}
	//如果还有为访问过的点
	while (!notvisitedyet.empty())
	{
		//将这个点作为起点开始DFS
		topological_sort(notvisitedyet.front());
	}
	for (int i : ans)
		cout << i << ' ';
}


#endif