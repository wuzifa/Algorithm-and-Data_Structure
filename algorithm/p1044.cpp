#ifdef RUN_P1044
//采用回溯算法算出所有可能
//卡特兰数
#include <iostream>
#include <chrono>
using namespace std;

static unsigned int ans = 0;


//Bounding Function:
//1.remain_num(输入序列剩余的元素个数) >= 0,等于0时说明输入序列的元素全部入栈完毕，所以小于0时可以kill node(没必要再递归下去了)
//2.buffer_num >= 0(缓冲栈当前元素个数，小于0时说明可以kill node了) 
//
//couting condition: 
//out_put_num == 输入序列元素总数,说明形成了一个完整的出栈序列,方案数加一
// 
//想看得清楚就画递归树
//每一步两个选择：
//入栈：从输入序列top_back并且pop_back一个数push_back到buffer_stack
//出栈：从buffer_stacktop_back并且pop_back一个数push_back到output_stack
//上述递归模拟过程会很自然地尝试并计数所有可能
struct Timer//计时器，在构造时开始计时，析构时结束计时
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	Timer() :
		start(std::chrono::high_resolution_clock::now()) {
	}

	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float ms = duration.count() * 1000.0f;
		cout << "Timer took " << ms << " ms" << endl;
	}
};
//void backtrack(int remain_num,int buffer_num, int now_output_num, int& data_num)
//{
//	if (remain_num < 0)//bounding function1
//		return;
//	if (buffer_num < 0)//bounding function2
//		return;
//	if (now_output_num == data_num)//couting_condition
//	{
//		ans++;
//		return;
//	}
//	backtrack(remain_num - 1, buffer_num + 1, now_output_num, data_num);//递归方向1：入栈
//	backtrack(remain_num, buffer_num - 1, now_output_num + 1, data_num);//递归方向2：出栈
//}用时：38s

//不要进入明知不可能的节点再退出，函数调用很耗时！！！

void backtrack(int remain_num, int buffer_num, int now_output_num, int& data_num)
{
	if (now_output_num == data_num)//couting_condition
	{
		ans++;
		return;
	}
	if(remain_num > 0)
		backtrack(remain_num - 1, buffer_num + 1, now_output_num, data_num);//递归方向1：入栈
	if(buffer_num > 0)
		backtrack(remain_num, buffer_num - 1, now_output_num + 1, data_num);//递归方向2：出栈
}//用时：24s

int main(void)
{
	int input_stack_size;
	cin >> input_stack_size;
	Timer timer;
	backtrack(input_stack_size, 0, 0, input_stack_size);
	cout << ans << endl;
}
#endif