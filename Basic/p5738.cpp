#ifdef RUN_P5738
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

class mycompare
{
public:	//别忘了声明在public权限下，否则sort算法访问不了
	bool operator()(int v1, int v2)
	{
		return v1 > v2;
	}
};

int main(void)
{
	int candidate, judge, sum;
	cin >> candidate >> judge;
	vector<int> score;
	vector<double> average_score;
	while (candidate--)
	{
		sum = 0;
		for (int i, j = 0; j < judge; j++)
		{
			cin >> i;
			score.push_back(i);
		}
		sort(score.begin(), score.end(), mycompare());//降序
		score.erase(score.begin());
		score.erase(score.end() - 1);//！！！注意，end返回的是末尾元素的下一个位置
		for (int num : score)
		{
			sum += num;
		}
		average_score.push_back((double)sum / score.size());
		score.clear();
	}
	sort(average_score.begin(), average_score.end(), mycompare());
	cout << fixed << setprecision(2) << *average_score.begin() << endl;
	return 0;
}

#endif