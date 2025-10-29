#ifdef RUN_P3370
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main(void)
{
	int num, h1, h2, base1 = 131, base2 = 13331;
	const int mod1 = (int)1e9 + 7, mod2 = (int)1e9 + 9;
	cin >> num;
	string str;
	set<pair<int, int>> hashValue;
	for (int i = 0; i < num; i++)
	{
		h1 = h2 = 0;
		cin >> str;
		for (char i : str)
		{
			h1 = (h1 * base1 + i) % mod1;
			h2 = (h2 * base2 + i) % mod2;
		}
		hashValue.insert(make_pair(h1, h2));
	}
	cout << hashValue.size();
}
#endif