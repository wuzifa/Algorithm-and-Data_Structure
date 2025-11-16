#ifdef RUN_P2360
#include <vector>
#include <iostream>
#include <deque>
using namespace std;
//思路：
//题目需要求到终点的最短路，采用广度优先搜索，原因：
//广度优先搜索会在每步探索会访问从"起点"开始的所有路的下一步，按"层级"拓展
//所以从起点出发如果最短路存在那么最短路会被BFS一步步探索出来，
//如果不存在BFS就始终在探索的过程中始终找不到终点，能很自然地找到最短路和判断最短路是否存在
//
//处理输入：把一层地牢按照二维数组存起来，再把每层地牢按照层数存在vector里
//在BFS时搜索方向有："上", "下", "左", "右", "上一层地牢相同位置", "下一层地牢相同位置" 
//！！！：在BFS搜索时注意别越界(地牢边界和层数边界)
//
//每BFS一步将 "步数"++，如果在BFS时发现终点则说明找到最短路
//
//BFS思路：
//需要的数据结构：
//1.一个队列(同来BFS)，
//2.地牢地图需要存储的不仅仅是那个点处的字符(能否访问)，还要存这个节点有没有被访问过的信息
//否则就会两个点间来回访问，或者重复访问已经访问过的点，陷入死循环
//所多维数组里面存结构体{(char)能否访问, (bool)是否访问过}

//当队列Q不空(循环)：
//		当队列Q不空(循环)：
//				选取队首的点进行explore(注意别explore已经explore的点，并且记得在开始算法前将起点设置为visited)
//				将新visit到的点入队temp
//				将队Q首的点出队
//		将temp中所有点入队Q
//这道题还加了如果发现出口直接退出所有循环
static struct node
{
	char m_c;
	bool m_visited;
	node()
		:m_c('a'), m_visited(false) {}
};

struct now_point
{
	int m_level;
	int m_row;
	int m_column;
	now_point(int level, int row, int column)
		:m_level(level), m_row(row), m_column(column) {}
};

int main()
{
	int level, row, column;
	cin >> level >> row >> column;
	vector<vector<vector<node>>> map(level, vector<vector<node>>(row, vector<node>(column)));
	string one_row;
	//下面用来记录起点位置
	//start_coordinate.first表示起点所在行数，start_coordinate.second表示起点所在列数
	deque<now_point> Q;
	for (int i = 0; i < level; i++)
	{
		for (int j = 0; j < row; j++)
		{
			cin >> one_row;
			for (int k = 0; k < one_row.size(); k++)
			{
				map[i][j][k].m_c = one_row[k];
				if (one_row[k] == 'S')
				{
					map[i][j][k].m_visited = true;
					Q.emplace_back(i, j, k);
				}
			}
		}
	}
	int step = 0;
	bool hasfoundexit = false;
	int npl, npr, npc;
	deque<now_point> temp;
	while (!Q.empty())
	{
		if (hasfoundexit)
			break;
		step++;
		//将队列中所有点探索完，探索过程中如果将为探索过的点加入队列
		while (!Q.empty())
		{
			npl = Q.front().m_level;
			npr = Q.front().m_row;
			npc = Q.front().m_column;
			//尝试访问同层左边的点
			if (npc - 1 >= 0 && map[npl][npr][npc - 1].m_c != '#' && !map[npl][npr][npc - 1].m_visited)
			{
				if (map[npl][npr][npc - 1].m_c == 'E')
				{
					hasfoundexit = true;
					break;
				}
				temp.emplace_back(npl, npr, npc - 1);
				map[npl][npr][npc - 1].m_visited = true;
			}
			//尝试访问同层右边的点
			if (npc + 1 < column && map[npl][npr][npc + 1].m_c != '#' && !map[npl][npr][npc + 1].m_visited)
			{
				if (map[npl][npr][npc + 1].m_c == 'E')
				{
					hasfoundexit = true;
					break;
				}
				temp.emplace_back(npl, npr, npc + 1);
				map[npl][npr][npc + 1].m_visited = true;
			}
			//尝试访问同层向上的点
			if (npr - 1 >= 0 && map[npl][npr - 1][npc].m_c != '#' && !map[npl][npr - 1][npc].m_visited)
			{
				if (map[npl][npr - 1][npc].m_c == 'E')
				{
					hasfoundexit = true;
					break;
				}
				temp.emplace_back(npl, npr - 1, npc);
				map[npl][npr - 1][npc].m_visited = true;
			}
			//尝试访问同层向下的点
			if (npr + 1 < row && map[npl][npr + 1][npc].m_c != '#' && !map[npl][npr + 1][npc].m_visited)
			{
				if (map[npl][npr + 1][npc].m_c == 'E')
				{
					hasfoundexit = true;
					break;
				}
				temp.emplace_back(npl, npr + 1, npc);
				map[npl][npr + 1][npc].m_visited = true;
			}
			//尝试访问上一层同一个位置的点
			if (npl - 1 >= 0 && map[npl - 1][npr][npc].m_c != '#' && !map[npl - 1][npr][npc].m_visited)
			{
				if (map[npl - 1][npr][npc].m_c == 'E')
				{
					hasfoundexit = true;
					break;
				}
				temp.emplace_back(npl - 1, npr, npc);
				map[npl - 1][npr][npc].m_visited = true;
			}
			//尝试访问下一层同一个位置的点
			if (npl + 1 < level && map[npl + 1][npr][npc].m_c != '#' && !map[npl + 1][npr][npc].m_visited)
			{
				if (map[npl + 1][npr][npc].m_c == 'E')
				{
					hasfoundexit = true;
					break;
				}
				temp.emplace_back(npl + 1, npr, npc);
				map[npl + 1][npr][npc].m_visited = true;
			}
			Q.pop_front();
		}
		Q = std::move(temp);
	}
	if (hasfoundexit)
		cout << "Escaped in " << step << " minute(s)." << endl;
	else
		cout << "Trapped!" << endl;
}

#endif