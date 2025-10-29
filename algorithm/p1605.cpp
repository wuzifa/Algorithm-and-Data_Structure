#ifdef RUN_P1605
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

static int route = 0;

struct Timer//计时器，在构造时开始计时，析构时结束计时
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	Timer():
		start(std::chrono::high_resolution_clock::now()) { }

	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float ms = duration.count() * 1000.0f;
		cout << "Timer took " << ms << " ms" << endl;
	}
};

void search_maze(int x, int y, vector<vector<int>>& ref)
{
	if (ref[x][y] == 0)
		return;
	if (ref[x][y] == 2)
	{
		route++;
		return;
	}
	ref[x][y] = 0;//经过上面判断后表示这个点可以作为路径上的点，所以在这里设为0
	search_maze(x + 1, y, ref);
	search_maze(x - 1, y, ref);
	search_maze(x, y + 1, ref);
	search_maze(x, y - 1, ref);
	ref[x][y] = 1;//此时函数retuern,表示这个点周围所有路径都已探索过，从这个点返回上一个点，也就是此时这个
//点不再是路径上的点，所以在这里设为1，以便后续其余路径探索将该店视为可经过点
}
//1表示这个格子可以走，2表示终点，0表示这个格子不可走
//0的三种情况：外围请，障碍，当前路径上的点

int main(void)
{
	
	int width, height, obstacle_num;
	int	s_x, s_y, e_x, e_y;
	int obstacle_x, obstacle_y;
	cin >> height >> width >> obstacle_num;
	cin >> s_x >> s_y >> e_x >> e_y;
	Timer timer;
	vector<vector<int>> maze(height + 2, vector<int>(width + 2, 1));//加2是为了设置外围墙

	for (int i = 0; i < width + 2; i++)
	{
		maze[0][i] = 0;
		maze[height + 1][i] = 0;
	}
	for (int j = 1; j <= height; j++)
	{
		maze[j][0] = 0;
		maze[j][width + 1] = 0;
	}

	maze[e_x][e_y] = 2;

	while (obstacle_num--)
	{
		cin >> obstacle_x >> obstacle_y;
		maze[obstacle_x][obstacle_y] = 0;
	}
	
	search_maze(s_x, s_y, maze);

	cout << route << endl;
	
}









#endif