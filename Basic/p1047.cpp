#ifdef RUN_P1047
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
	int length, area_num, start, end, ans = 0;
	cin >> length >> area_num;
	vector<int> road(length + 1, 1);
	while (area_num--)
	{
		cin >> start >> end;
		fill(road.begin() + start, road.begin() + end + 1, 0);
	}
	for (int i : road)
	{
		if (i)
			ans++;
	}
	cout << ans << endl;

}

#endif