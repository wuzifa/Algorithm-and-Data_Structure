#ifdef RUN_P1451
#include <vector>
#include <iostream>
#include <string>
using namespace std;

//网格连通块

static vector<string> map;
//visit过的节点不要再运行搜索
//在深度优先搜索算法如果没有visited指引算法正确搜索方向，搜索算法会走回头路陷入死循环
static vector<vector<bool>> visited;
static int row, column;

//进入每个点后向上下左右四个方向递归搜索(在进入搜索前检查是否要对这个点进行搜索)
void DFS_search(int x, int y)
{
	visited[x][y] = true;
	//下面if()内部语句的先后顺序不要写错了！！
	//1.检查数组下表是否越界永远在访问数组这个下标的前面！！
	//2.检查下个准备搜索的点是否为"细胞"一部分
	//3.检查下个准备搜索的点是否已经搜索过
	if (x - 1 >= 0 && map[x - 1][y] != '0' && !visited[x - 1][y])
		DFS_search(x - 1, y);
	if (x + 1 < row && map[x + 1][y] != '0' && !visited[x + 1][y])
		DFS_search(x + 1, y);
	if (y - 1 >= 0 && map[x][y - 1] != '0' && !visited[x][y - 1])
		DFS_search(x, y - 1);
	if (y + 1 < column && map[x][y + 1] != '0' && !visited[x][y + 1])
		DFS_search(x, y + 1);
}

int main(void)
{
	int cell_num = 0;
	cin >> row >> column;
	map = std::move(vector<string>(row, string()));
	visited = std::move(vector<vector<bool>>(row, vector<bool>(column, false)));
	for (int i = 0; i < row; i++)
	{
		cin >> map[i];
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			// 遍历整张图，找到为'0'并且没访问过的点进行搜索，把这个细胞搜索完，
			// 在搜索的过程中同时标记细胞的每个点为访问过
			// 每次找到一个上面的点说明找到一个还没被搜索过的细胞
			if (!visited[i][j] && map[i][j] != '0')
			{
				cell_num++;
				DFS_search(i, j);
			}
		}
	}
	cout << cell_num << endl;
	return 0;
}

#endif