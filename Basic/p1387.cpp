#ifdef RUN_P1387
#include <iostream>
#include <vector>
using namespace std;

//一维前缀和维护一维区间内的和(一段线段含的数字的和)
//那么二维前缀和就是维护二维区间内的和(一片面积含的数字的和)

//0 0 0 0 0 0 
//0 . . . . .
//0 . . . . .
//0 . . . . .
//0 . . . . .
//0 . . . . .
//table[x][y]表示(0, 0)为左上角, (x, y)为右下角的矩形内数字的和(在部分时候也可理解为(1, 1)为左上角, (x, y)为右下角的矩形内数字的和)

//二维前缀和

//建表:
//table[x][y] = table[x][y - 1] + table[x - 1][y] + table[x - 1][y - 1]
//(x表示行，即数组下表的第一个元素, y表示列，即数组下表的第二个元素，table[x - 1]]y - 1]是多减的部分，简单容斥原理)

//查询左上角坐标为(x1, y1)，右下角为(x2, y2)的矩形内数字和:
//sum = table[x2][y2] - table[x2][y1 - 1] - table[x1 - 1][y2] + table[x1 - 1][y1 - 1](table[x1 - 1][y1 - 1]是多减的部分)

//注意:
//在建表时应该将表的长宽设置得比输入的矩阵的长宽都大1
int main(void)
{
	vector<vector<int>> table;
	int length, width;
	cin >> length >> width;
	table.resize(length + 1);
	for (int i = 0; i < length + 1; i++)
	{
		table[i].resize(width + 1);
	}
	//建立二位前缀和table
	int data;
	for (int row = 1; row < length + 1; row++)
	{
		for (int column = 1; column < width + 1; column++)
		{
			cin >> data;
			table[row][column] = data + table[row][column - 1] + table[row - 1][column] - table[row - 1][column - 1];
		}
	}
	
	//如果在边长为某个值循环整个二位前缀和表没找到符合要求的正方形，就不用继续找了，因为有(n + 1)为边长的正方形则必有n为边长的正方形
	bool findsquare = true;
	int loop_width = 2;
	int x1, y1, x2, y2, start_point;
	while (findsquare && (loop_width < min(length, width)))
	{
		findsquare = false;
		start_point = loop_width;
		int num = loop_width * loop_width;
		for (x2 = start_point, x1 = 1; x2 < length + 1; x2++, x1++)
		{
			if (findsquare)
				break;
			for (y2 = start_point, y1 = 1; y2 < width + 1; y2++, y1++)
			{
				if (findsquare)
					break;
				if (table[x2][y2] - table[x2][y1 - 1] - table[x1 - 1][y2] + table[x1 - 1][y1 - 1] == num)
				{
					loop_width++;
					findsquare = true;
				}
			}
		}
	}
	cout << loop_width - 1 << endl;
}

#endif