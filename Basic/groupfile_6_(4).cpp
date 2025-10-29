#ifdef RUN_GROUPFILE64
#include <iostream>
using namespace std;
void up_func();
void down_func();
void right_func();
void left_func();

int x = 0;
int y = 0;

int left_bound = 0, top_bound = 0;
int right_bound, bottom_bound;


void(*move_index)();

void changeindex(void(*operation)())
{
	operation();
}

void up_func()
{
	if(x > top_bound)
		x--;
	else
	{
		move_index = right_func;
		left_bound++;
		changeindex(right_func);
	}
}

void down_func()
{
	if (x < bottom_bound)
		x++;
	else
	{
		move_index = left_func;
		right_bound--;
		changeindex(left_func);
	}
}

void right_func()
{
	if (y < right_bound)
		y++;
	else
	{
		move_index = down_func;
		top_bound++;
		changeindex(down_func);
	}
}

void left_func()
{
	if (y > left_bound)
		y--;
	else
	{
		move_index = up_func;
		bottom_bound--;
		changeindex(up_func);
	}
}



int main(void)
{
	int width;
	cin >> width;
	int num = width * width;
	
	
	left_bound = 0;
	top_bound = 0;
	right_bound = width - 1;
	bottom_bound = width - 1;
	int** forest = new int* [width];
	for (int i = 0; i < width; i++)
	{
		forest[i] = new int[width];
	}
	move_index = right_func;
	for (int i = 1; i <= width * width; i++)
	{
		forest[x][y] = i;
		if(i < width * width)
			changeindex(move_index);

	}
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (forest[i][j] < 10)
				cout << forest[i][j] << "   ";
			else
				cout << forest[i][j] << "  ";
		}
		cout << endl;
	}

	return 0;
}



#endif