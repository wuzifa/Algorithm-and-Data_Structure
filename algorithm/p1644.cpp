#ifdef RUN_P1644
#include <iostream>
#include <vector>
using namespace std;

static vector<vector<unsigned int>> state_table;
static vector<vector<bool>> visited;
static int row_max;
//访问滚动数组的一列时可能行下表大于5，导致dp表被污染
//实际可以直接建一个数组，这个数组的空间利用率不会很低，并且行数和列数也不是很大，完全可接受

// 利用递归自然递推，state_table[x][y] = state_table[x - 1][y - 2] + state_table[x - 2][y - 1] + state_table[x + 1][y - 2] + state_table[x + 2][y - 1]
// (后面加上的前提是那个下标代表的点在棋盘里面)
// 不要直接DFS求解原点可以到达的所有点的路径数，这样会计算大量无法到达右上角的点的路径数，浪费时间 
unsigned int dfs_table(int row, int column)
{
	if (column == 0 && row == 0)
		return 1;
	//记忆化
	if (visited[row][column])
		return state_table[row][column];
	if (row + 2 <= row_max && column - 1 >= 0)
		state_table[row][column] += dfs_table(row + 2, column - 1);
	if (row + 1 <= row_max && column - 2 >= 0)
		state_table[row][column] += dfs_table(row + 1, column - 2);
	if (row - 1 >= 0 && column - 2 >= 0)
		state_table[row][column] += dfs_table(row - 1, column - 2);
	if (row - 2 >= 0 && column - 1 >= 0)
		state_table[row][column] += dfs_table(row - 2, column - 1);
	visited[row][column] = true;
	return state_table[row][column];
}

int main()
{
	int column;
	cin >> row_max >> column;
	visited = std::move(vector<vector<bool>>(row_max + 1, vector<bool>(column + 1, false)));
	state_table = std::move(vector<vector<unsigned int>>(row_max + 1, vector<unsigned int>(column + 1, 0)));
	cout << dfs_table(row_max, column) << endl;
}

#endif