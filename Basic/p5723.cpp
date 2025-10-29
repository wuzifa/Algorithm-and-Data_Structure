#ifdef RUN_P5723
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

bool isPrimeNum(int n)
{
	if (n <= 1)
		return false;
	if (n == 2 || n == 3)
		return true;
	if (n % 2 == 0)
		return false;
	for (int i = 3; i <= sqrt(n); i += 2)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}


int main(void)
{
	int capacity, sum = 0, i = 2;
	vector<int> bag;
	cin >> capacity;
	while (true)
	{
		if (isPrimeNum(i))
		{
			sum += i;
			if (sum <= capacity)
				bag.push_back(i);
			else
				break;
		}
		i++;
	}
	for (int j : bag)
	{
		cout << j << endl;
	}
	cout << bag.size();
	return 0;
}



#endif