#ifdef RUN_P1481
#include <iostream>
#include <string>
using namespace std;

// 动态规划算法 
// 类似最长上升子序列，但是是字符串版本的
// 题目思路：
// 题目的子问题是一某个单词为结尾的最长词链的长度 
// 解决这个子问题的前提子问题是这个单词的前缀的单词作为结尾的最长词链的长度，
// 子问题间关系是 max_length(wordⁿ) = max(max_length(wordⁱ) + 1)其中wordⁱ为wordⁿ的前缀 
// 然后解决子问题的顺序是先求短的单词的最长词链长度
// 注意这题的输入按字典顺序排列，所以输入中一个单词的前缀只可能出现在这个单词的前面，不可能在后面
// wordⁱ怎么找，遍历wordⁿ前面每一个单词调用string的find()函数,如果返回值为0则说明这个单词是前缀

int main(void)
{
	//直接通过下标将每个单词的dp和它的dp值联系起来
	unsigned int dp[2001], word_num;
	string word[2001];
	cin >> word_num;
	unsigned int max_chain = 0, max_preqequisite;
	// 遍历每个单词求dp[i](最长词链长度)，同时也符合解决子问题的顺序，
	// 对于每个单词它的前提子问题在单词的前面，所以对于输入按正常顺序处理即可
	for (unsigned int i = 0; i < word_num; i++)
	{
		cin >> word[i];
		string now_word = word[i];
		//dp[pre_fix]肯定是正数，所以max_preqequisite初始化为0
		max_preqequisite = 0;
		//遍历第i个单词前面的单词，找出前缀并且求出dp[pre_fix]_max
		for (unsigned int j = 0; j < i; j++)
		{
			if (now_word.find(word[j]) == 0)
				max_preqequisite = max(max_preqequisite, dp[j]);
		}
		dp[i] = max_preqequisite + 1;
		//顺便每轮循环判断一下是否更新max_chain,相当与每轮循环里把找出dp[i]最大值的工作做了
		max_chain = max(max_chain, dp[i]);
	}
	cout << max_chain << endl;
}

#endif