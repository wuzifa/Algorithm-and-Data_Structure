#ifdef RUN_P1162
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
//采用的BFS搜索遍历图
// 两个出现过的错误点：
// 1.auto initzero_coord = findboardzero();
// 这句initzero_coord的值依赖findboardzero()来设置，但是findboardzero()不一定有返回值，
// 因为findboardzero()中返回pair是有条件的，比如方阵外周全是1，此时就没有返回值，initzero_coord就是一个随机值,
// 拿着随机值去调用explore_map就会出现vector访问越界，报段错误
// 以后出现这种有返回值的函数一定要确保它有返回值(即使是标记错误的标志量)
// 题目判断是否被包围的0的标准：如果从某个 0 出发，只向上下左右 4 个方向移动且仅经过其他 0 的情况下，无法到达方阵的边界，就认为这个 0 在闭合圈内。闭合圈不一定是环形的，
// 可以是任意形状，但保证闭合圈内的 0 是连通的（两两之间可以相互到达）。
// 2.这道题一定得用多源BFS，即把方阵边界上所有为0的点作为BFS起点，否则如果只随便在边界上找一个为0的点
// 作为起点时，当题目输入为比如：
// 1 0 1 1 1
// 1 1 1 1 1
// 0 0 1 0 0
// 1 1 1 1 1
// 1 1 1 1 1
// 如果只拿第一行中的0作为起点，第三行的0就全是漏网之鱼
// 必须把所有边界上的 0 都作为 BFS 的起点一次性入队（多源 BFS），否则只从单个起点 BFS 会只标记到该起点所在的那个外部连通分量，
// 其他与边界连通但与该起点不连通的外部 0 会被误判为“内部”并改成 2
static vector<vector<int>> map;
static vector<vector<int>> notset;//存储是否设置过的信息，
//两个用途：
//1.防止在广度优先搜索时反复在两个点之间来回，陷入死循环
//2.在多源BFS时可以不用继续设置已经设置过的点
static queue<pair<int, int>> tobeexplored;
static int square_width;
//注意下面pair中第一个元素表示填在map[][]的第一个括号，不要用x, y理解
void findboardzero()//找到边界上所有为0的点并push进to_be_explored queue
{
	int last_column_bound = map.size();
	int last_row = map.size() - 1;
	for (int i = 0; i < last_column_bound; i++)
	{
		if (!map[0][i])
		{
			tobeexplored.emplace(0, i);
			notset[0][i] = 0;//设置notset，相当于手动检查过这个点了，不用再在rxplore_map函数中检查这个点
			map[0][i] = -1;
		}
	}
	for (int i = 0; i < last_column_bound; i++)
	{
		if (!map[last_row][i])
		{
			tobeexplored.emplace(last_row, i);
			notset[last_row][i] = 0;
			map[last_row][i] = -1;
		}
	}
	for (int i = 1; i < last_row; i++)
	{
		if (!map[i][0])
		{
			tobeexplored.emplace(i, 0);
			notset[i][0] = 0;
			map[i][0] = -1;
		}
	}
	for (int i = 1; i < last_row; i++)
	{
		if (!map[i][last_column_bound - 1])
		{
			tobeexplored.emplace(i, last_column_bound - 1);
			notset[i][last_column_bound - 1] = 0;
			map[i][last_column_bound - 1] = -1;
		}
	}
}
void set_map(pair<int, int> coordinate)
{
	if (!map[coordinate.first][coordinate.second])
	{
		map[coordinate.first][coordinate.second] = -1;//将与边界0连通的0设置为-1，与"被包围的0区分开"
		tobeexplored.emplace(coordinate.first, coordinate.second);//只能把为0的点的坐标push进tobeexplored，否则如果把1也push进的话
		//1内部的0也会被set_map误设为-1，相当于把1围城的屏障破了
	}

	notset[coordinate.first][coordinate.second] = 0;//set_map函数处理过的点要在not_set中设为否，否则陷入死循环
}
void explore_map()//广度优先搜索
{
	while (!tobeexplored.empty())
	{
		int x = tobeexplored.front().first;
		int y = tobeexplored.front().second;
		if (x - 1 >= 0 && notset[x - 1][y])//下面是四个BFS方向
		{
			set_map(make_pair(x - 1, y));
		}
		if (x + 1 < square_width && notset[x + 1][y])//没有越界并且没设置过的点则进入set_map函数进行设置
		{
			set_map(make_pair(x + 1, y));
		}
		if (y - 1 >= 0 && notset[x][y - 1])
		{
			set_map(make_pair(x, y - 1));
		}
		if (y + 1 < square_width && notset[x][y + 1])
		{
			set_map(make_pair(x, y + 1));
		}
		tobeexplored.pop();
	}
}


int main(void)
{
	int width;
	cin >> width;
	square_width = width;
	map.resize(width);
	notset.resize(width);
	for (int i = 0; i < width; i++)
	{
		map[i].resize(width);
		notset[i].resize(width, 1);
	}
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cin >> map[i][j];
		}
	}
	//auto initzero_coord = findboardzero();
	//map[initzero_coord.first][initzero_coord.second] = -1;
	//tobeexplored.push(initzero_coord);
	//notset[initzero_coord.first][initzero_coord.second] = 0;
	findboardzero();
	if (!tobeexplored.empty())
	{
		explore_map();
		for (auto i : map)
		{
			for (auto j : i)
			{
				switch (j)
				{
				case -1:
					cout << 0 << ' ';
					break;
				case 1:
					cout << 1 << ' ';
					break;
				case 0:
					cout << 2 << ' ';
				}

			}
			cout << endl;
		}
	}
	else
	{
		for (auto i : map)
		{
			for (auto j : i)
			{
				if (j)
					cout << 1 << ' ';
				else
					cout << 2 << ' ';
			}
			cout << endl;
		}
	}
}

#endif