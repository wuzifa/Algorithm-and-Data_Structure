#ifdef RUN_P1496
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

struct compareendpoint_less
{
	bool operator()(pair<int, int>& a, pair<int, int>& b)
	{
		return a.first < b.first;
	}
};

//采用离散化解决，题目如果设置每个烧过的点，首先点的数量庞大，内存不够，其次可能也超时(大量点重复设置)
//保留关键信息(燃烧区域的左右端点)，去掉不重要的信息(两个端点中间的部分)
//将所有端点保存进数组内，燃烧区域左右端点之间的数组区域设为"燃烧状态"
// 例如有两个燃烧区间(3, 10), (7, 15)
//1 2 3  4  5 ......
//3 5 7 10  15
//1 1 1  1
//    1  1   1
//最后遍历整个端点数组查找如果是燃烧状态，则后面的值减前面的值为一个燃烧区间部分，加进答案
//上面是区间修改，见最下面的说明
int main(void)
{
	int seg_num;
	cin >> seg_num;
	//vector<pair<int, bool>> end_point;
	vector<pair<int, int>> endpoint_diff(seg_num * 2);
	endpoint_diff.reserve(seg_num * 2);
	vector<pair<int, int>> end_pair(seg_num);
	int a, b;
	for (int i = 0; i < seg_num; i++)
	{
		cin >> a >> b;
		end_pair[i].first = a;
		end_pair[i].second = b;
		endpoint_diff.emplace_back(a, 0);
		endpoint_diff.emplace_back(b, 0);
	}
	sort(endpoint_diff.begin(), endpoint_diff.end(), compareendpoint_less());
	auto duplicate_begin = unique(endpoint_diff.begin(), endpoint_diff.end());
	endpoint_diff.erase(duplicate_begin, endpoint_diff.end());
	map<int, int> find_index;
	size_t size = endpoint_diff.size();
	for (int i = 0; i < size; i++)
	{
		find_index.insert(make_pair(endpoint_diff[i].first, i));
	}
	for (auto p : end_pair)
	{
		endpoint_diff[find_index.at(p.first)].second += 1;
		endpoint_diff[find_index.at(p.second)].second -= 1;
	}
	int sum = 0, now_point = 0;
	for (auto it = endpoint_diff.begin(); it != endpoint_diff.end() - 1; it++)
	{
		now_point += it->second;
		if (now_point)
			sum += ((it + 1)->first - it->first);
	}
	cout << sum << endl;
	return 0;
}

//下面属于数组的区间修改，如果区间跨度很大，就超时，用差分思想
//原本是判断原数组每个点处的bool值是否为true,现在变为判断晕啊数组每个点处的值是否>0(原来某个区间设为true --> 现在这个区间加1)
// 由于最后是从左向右遍历整个原数组求值，不会跳跃着或者多次求原数组不同的点，所以对差分数组的遍历求和只要从左向右一次，不会多次遍历差分数组很大区间
//vector<pair<int, bool>> end_point;
//for (auto p : end_pair)
//{
//	for (int i = find_index.at(p.first); i <= find_index.at(p.second) - 1; i++)
//	{
//		end_point[i].second = true;
//	}
//}
//原数组区间：[l, r]中每个元素加k(k可为负数)
//差分数组变化：dif[l] += k, dif[r + 1] -= k
//要查询原数第i个位置的值，对差分数组求前缀和求到i即可

#endif
