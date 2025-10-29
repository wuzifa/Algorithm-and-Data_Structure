#ifdef RUN_P2240
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Coins
{
	int weight, profit;
	double cost_perf;
	Coins(int p, int w):profit(p), weight(w), cost_perf((double)p / w) {}
};

class myCompare
{
public:
	bool operator()(const Coins& a, const Coins& b)
	{
		return a.cost_perf > b.cost_perf;
	}
};


int main(void)
{
	int N, capacity, profit, weight;
	double ans = 0;
	cin >> N >> capacity;
	vector<Coins> data;
	data.reserve(N);
	for (int i = 0; i < N; i++)
	{
		cin >> weight >> profit;
		data.push_back(Coins(profit, weight));
	}
	sort(data.begin(), data.end(), myCompare());
	vector<Coins>::const_iterator it = data.begin();
	while (capacity > 0 && it != data.end())
	{
		if (capacity - it->weight >= 0)
		{
			ans += it->profit;
			capacity -= it->weight;
		}
		else
		{
			ans += ((double)capacity / it->weight) * it->profit;
			capacity = 0;
		}
		it++;
	}
	cout << fixed << setprecision(2) << ans << endl;
}
#endif
