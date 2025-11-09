#ifdef RUN_P2799
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// 每次判断后面半段经过翻转后和前面半段相不相等，相等则继续对前面半段进行同样的判断，
// 直到后面半段和前面半段不相等，这时候就找出了答案
int min_serach(string& str, int end)
{
	// 下面这句是为了两种特殊情况:
	// 1.已经检查到只剩一个字母(end等于0了，符合下面条件)
	// 2.检查当前字母段时有奇数个字母(end为偶数)，此时这段字母与必定不是镜子照出来的
	// 因为镜子找出来的字母段是原先的字母段翻倍，新的字母段字母个数必定是偶数
	if (end % 2 == 0)
		return (end + 1);
	int post_start, half_len;
	// 原先在这里有下面这样一段：
	// if (str.substr(post_start, half_len) == str.substr(0, half_len))
	// 	return min_serach(str, post_start - 1);
	// 这样一段会误判当前字母段为"镜子找出来的"，的确在经过镜子两次照射后后面镜子新生成的字母段因为
	// 生成它的字母段已经是左右镜像对称的而"新字母段"和"生成它的字母段"在新字母段不reverse的情况下直接就相等
	// 但是直接相等是照射两次后"为镜子找出来的"必要非充分条件，例如如果出现: "ABCDABCD"这样的字母段就会有漏网之鱼
	// 所以还是老老实实地先反转再判断相不相等，这个是充要条件
	post_start = half_len = (end + 1) / 2;
	string reversed = str.substr(post_start, half_len);
	std::reverse(reversed.begin(), reversed.end());
	if (str.substr(0, half_len) != reversed)
		return (end + 1);
	else
		return min_serach(str, post_start - 1);
		
}

int main()
{
	string necklace;
	cin >> necklace;
	cout << min_serach(necklace, necklace.size() - 1) << endl;
}

#endif
