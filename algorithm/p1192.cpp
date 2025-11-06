#ifdef RUN_P1192
#include <vector>
#include <iostream>
using namespace std;
 
// 线性递推，后面的值由前面的值算得，先求前面的值(smaller problem)，后求后面的值(larger problem)
// 类似动态规划中的状态转移，解决大问题需要先解决小问题
// 递推公式：F(n) = F(n - 1) + F(n - 2) + F(n - 3) + ... + F(n - k)
// 跨上第n阶台阶可以从 第(n - 1)阶，第(n - 2)阶，第(n - 3)阶， ...，第(n - k)阶跨上去(子问题之间的关系)
// n为台阶数，k为每次最高可以跨的台阶数目

int main(void)
{
	int stairs, step_range;
	cin >> stairs >> step_range;
	//特殊情况可以直接得到答案就直接输出并退出
	if (step_range == 1)
	{
		cout << 1 << endl;
		return 0;
	}
	//下面这样去数组大小是防止一次跨的数目超过总台阶数
	vector<unsigned int> F(max(stairs + 1, step_range + 1), 0);
	F[0] = F[1] = 1;
	//初始化前step_range项
	for (int i = 2; i <= step_range; i++)
	{
		for (int j = 0; j < i; j++)
		{
			//%100003可以边加边取余，取余其实相当于把溢出100003的部分折叠到100003里面，对最终答案没有影响
			F[i] = (F[i] + F[j]) % 100003;
		}
	}
	//处理特殊情况，当step_range > stairs时，即一次跨的数目超过总台阶数
	if (step_range >= stairs)
	{
		cout << F[stairs] << endl;
		return 0;
	}
	//根据递推公式求数组后面的元素
	for (int i = step_range + 1; i <= stairs; i++)
	{
		for (int j = 1; j <= step_range; j++)
		{
			F[i] = (F[i] + F[i - j]) % 100003;
		}
	}
	cout << F[stairs] << endl;
}

#endif