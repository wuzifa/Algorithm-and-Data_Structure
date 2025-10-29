
#ifdef RUN_P1996
#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main(void)
{
	int n, m ,count = 1;
	cin >> n >> m;
	queue<int> Q;
	for (int i = 1; i < (n + 1); i++)
		Q.push(i);
	while (!Q.empty())
	{
		if (count == m)//检查当前人报的数
		{
			cout << Q.front() << " ";
			Q.pop();
			count = 1;//下一个人从1开始报
		}
		else
		{
			Q.push(Q.front());
			Q.pop();           //让人出队再入队实现循环的效果，即n个人围城一圈
			count++;           //下一个人报的数加1
		}
	}
}
#endif