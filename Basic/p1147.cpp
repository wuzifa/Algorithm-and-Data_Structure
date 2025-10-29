#ifdef RUN_P1147
#include <iostream>
#include <vector>

using namespace std;



int main(void)
{
	unsigned int M;
	cin >> M;

	unsigned int sum;
	unsigned int j;
	for (unsigned int i = 1; i < M / 2 + 6; i++)
	{
		j = i + 1;
		sum = i + (i + 1);
		while (sum <= M)
		{
			if (sum == M)
			{
				cout << i << ' ' << j << endl;
				break;
			}
			j++;
			sum += j;
		}
	}
	return 0;
}

#endif