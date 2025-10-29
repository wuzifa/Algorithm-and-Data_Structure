#ifdef RUN_P2242
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main(void)
{
	int hole_num, close, hole_coord;
	cin >> hole_num >> close;
	vector<int> hole;
	vector<int> hole_gap;
	while (hole_num--)
	{
		cin >> hole_coord;
		hole.push_back(hole_coord);
	}
	for (auto it = hole.begin(); it != hole.end() - 1; it++)
	{
		hole_gap.push_back(*(it + 1) - *it);
	}
	sort(hole_gap.begin(), hole_gap.end(), greater<int>());
	auto it = hole_gap.begin();
	int maximum_gap = 0;
	while (--close)
	{
		maximum_gap += (*it - 1);
		it++;
	}
	cout << (*(hole.end() - 1) - *(hole.begin()) + 1 - maximum_gap) << endl;
	return 0;
}
#endif