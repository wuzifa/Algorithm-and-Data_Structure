#ifdef RUN_BITMASK
#include <iostream>
using namespace std;


//显示这个subset(每个元素在subset中是否存在)
template<typename T>
void display(T subset)
{
	//遍历每个bit查看它是否为0
	for (int bit_no = 0; bit_no < sizeof(T) * 8; bit_no++)
	{
		if (subset & (T(1) << bit_no))
		{
			//表示第bit_no + 1个元素在子集中
			cout << 1 << ' ';//后面实现真正相关逻辑时把这里删了
		}
		else
			cout << 0 << ' ';//后面实现真正相关逻辑时把这里删了
	}
	cout << endl;//后面实现真正相关逻辑时把这里删了
}

template<typename T>
void remove(T& subset, int index)
{
	if (index < sizeof(T) * 8)
	{
		if (subset & (T(1) << (index - 1)))
			subset ^= (T(1) << (index - 1));
	}
}

template<typename T>
void add(T& subset, int index)
{
	if (index < sizeof(T) * 8)
	{
		if (!(subset & (T(1) << (index - 1))))
			subset ^= (T(1) << (index - 1));
	}
}

int main(void)
{
	long long subset = 15;
	remove<long long>(subset, 2);
	add<long long>(subset, 63);
	display<long long>(subset);
}






#endif