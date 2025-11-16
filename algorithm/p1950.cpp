#ifdef RUN_P1191
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

//蛮力法：将图中所有为1的点遍历一遍，作为矩形M的左上角
//       有序向右下拓展M的长和宽，在拓展长或宽的时候遇到0则停止拓展长或宽，因为再拓展则矩形肯定不符合规则
//       worst case: 
//                  假设图长和宽相等为n，遍历每个点为n²，如果每个矩形在拓展的时候不会遇到任何0，则每个矩形的cost又为n²，总的为n⁴



// 递推法: 
// 子问题: 一个点(i, j)作为右下角时所有可能的矩形的数量sub(i, j)
// 递推公式: sub(i, j) = height * width + sub(i, p)(！！！！后面这项可能不加，详情见第27, 28行说明)
// 遍历方向: 从上到下，从左到右遍历
// height: 当前这个点向上的连续1最长能连续多少个1   ---->在这里需要存储每个点的height
// p: 在同一行内，第一个小于height的点所在列数      
//		---->找一个数列(这一行每个点的height)每个数左边第一个小于这个数的位置在哪: 用单调栈
// width: j - p
// 细节问题: 单调栈存什么?: 点所在列数，点的height
// 值为0的点Z高度取多少?: 0  并且sub(Z) = 0  
// 求解每一行中每个元素左边第一个height小于它的点使用单调栈的思路:
// 从左向右遍历这一行每个点(循环):
//		从上至下将当前栈内大于等于当前点height的所有元素全部出栈
//		(循环做直到栈为空或者找到一个更小的元素(并记录下标，如果此时栈为空，那就意味着左边没有比当前这个点height更小的点，
//		此时p = 0, 并且只有当左边存在height比自己更小的点时才应该加上sub(i, p), 否则就是纯全部为1的矩形情况，直接height * width))
// 
// 后面再改进了一下，不将子问题地推关系两种情况分开处理，通过对单点栈入特殊元素来解决上面问题
// 
// 递推法相当于改进版蛮力法，也是将所有点作为矩形右下角，求出此时有多少种矩形，但是利用了子问题间的联系
// 



struct node1
{
	char m_c;
	int m_height;
	unsigned int m_dp;
	node1()
		:m_c('a'), m_dp(0), m_height(0) {}
};

struct node2
{
	int m_column;
	int m_height;
	node2(int column, int height)
		:m_column(column), m_height(height) {}
};

int main()
{
	int row, column;
	cin >> row >> column;
	vector<vector<node1>> dp(row, vector<node1>(column));
	string one_row;
	//读取整张01矩阵
	for (int i = 0; i < row; i++)
	{
		cin >> one_row;
		for (int j = 0; j < column; j++)
		{
			dp[i][j].m_c = one_row[j];
		}
	}
	int now_row;
	int height_sum;
	//计算矩阵中每个点的height
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			now_row = i; height_sum = 0;
			while (now_row >= 0)
			{
				if (dp[now_row][j].m_c == '*')
					break;
				height_sum++; now_row--;
			}
			dp[i][j].m_height = height_sum;
		}
	}
	stack<node2> monotonic_stack;
	int width, height, p;
    //答案可能很大,一定要开long long
	long long total_num = 0;
	unsigned int subprod_dp;
	for (int i = 0; i < row; i++)
	{
		//开始遍历这一行的每个元素前把单调栈清空
		while (!monotonic_stack.empty())
			monotonic_stack.pop();
		//插入特殊元素，为了解决"当前遍历的点左边有小于这个点height的点"
		monotonic_stack.emplace(-1, -1);
		for (int j = 0; j < column; j++)
		{
			//根据这题情况的单调栈插入操作
			while (!monotonic_stack.empty() && monotonic_stack.top().m_height >= dp[i][j].m_height)
				monotonic_stack.pop();
			p = monotonic_stack.top().m_column;
			width = j - p; height = dp[i][j].m_height;
			monotonic_stack.emplace(j, dp[i][j].m_height);
			if (p >= 0)
				subprod_dp = dp[i][p].m_dp;
			else
				subprod_dp = 0;
			dp[i][j].m_dp = width * height + subprod_dp;
			total_num += dp[i][j].m_dp;
		}
	}
	std::cout << total_num << endl;
}

#endif