#ifdef RUN_P1331 
#include <vector>
#include <iostream>
using namespace std;

static int left_bound, up_bound, right_bound, bottom_bound;
static int row, column;
static vector<vector<char>> map;
static vector<vector<bool>> visited;
// 题目两个要求：
// 1.船只是矩形
// 2.不同船只不能相邻

//常规思路: 将所有符合要求的船只求出来后再判断是否相邻

// 我的转化：
// 不判断不同船只不能相邻这个点(不好判断)，
// 如果两艘矩形船只相邻，那这两搜船拼成的大船肯定不是矩形(否则这两艘小船在常规思路中找出图中所有船只的阶段早就合并成一艘大船了)
// 所以就有下面我的思路：
// 
// 1.将所有连在一起的#视作一艘船
// 2.判断这艘船是不是矩形并且实心的

//广搜找出这艘船的外围矩形
static void DFS_search(int x, int y)
{
	visited[x][y] = true;
	//老是数组访问越界！！！
	//那就在访问数组某个下标前检查下标是否out of range
	if (x - 1 >= 0 && !visited[x - 1][y] && map[x - 1][y] == '#')
	{
		up_bound = x - 1;
		DFS_search(x - 1, y);
	}
	if (x + 1 < row && !visited[x + 1][y] && map[x + 1][y] == '#')
	{
		bottom_bound = x + 1;
		DFS_search(x + 1, y);
	}
	if (y - 1 >= 0 && !visited[x][y - 1] && map[x][y - 1] == '#')
	{
		left_bound = y - 1;
		DFS_search(x, y - 1);
	}
	if (y + 1 < column && !visited[x][y + 1] && map[x][y + 1] == '#')
	{
		right_bound = y + 1;
		DFS_search(x, y + 1);
	}
}

bool checkship(int x, int y)
{
	//初始化外围矩形的上下左右边界
	left_bound = right_bound = y;
	up_bound = bottom_bound = x;
	//广搜找出这艘船的外围矩形
	DFS_search(x, y);
	//检查这个外围矩形内是否全是#，即这个船只符不符合矩形要求
	for (int m_row = up_bound; m_row <= bottom_bound; m_row++)
	{
		for (int m_column = left_bound; m_column <= right_bound; m_column++)
		{
			if (map[m_row][m_column] == '.')
				return false;
		}
	}
	return true;
}

int main(void)
{
	cin >> row >> column;
	map = std::move(vector<vector<char>>(row, vector<char>(column)));
	visited = std::move(vector<vector<bool>>(row, vector<bool>(column, false)));
	string line;
	for (int i = 0; i < row; i++)
	{
		cin >> line;
		for (int j = 0; j < column; j++)
		{
			map[i][j] = line[j];
		}
	}
	int ship_num = 0;
	bool validship = true;
	for (int i = 0; i < row; i++)
	{
		if (!validship)
			break;
		for (int j = 0; j < column; j++)
		{
			if (!validship)
				break;
			if (map[i][j] == '#' && !visited[i][j])
			{
				ship_num++;
				validship = checkship(i, j);
			}
		}
	}
	if (validship)
		cout << "There are " << ship_num << " ships." << endl;
	else
		cout << "Bad placement." << endl;
	return 0;
}

#endif