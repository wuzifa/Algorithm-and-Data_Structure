#ifdef RUN_P1177
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime> 
using namespace std;

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

int Partition(vector<int>& list, int l, int r)//注意：l为要排序的list的最左边一个数的索引，r为最右边一个数的再右边一个索引(这里将r视作list的结尾标志)
{
	int pivot_index = l + rand() % ((r - 1) - l + 1), i, j;
	swap(list[l], list[pivot_index]);
	int pivot = list[l];
	i = l; 
	j = r;
	while (i < j)
	{
		do 
		{
			i++;
		} while (list[i] <= pivot);
		do 
		{
			j--;
		} while (list[j] > pivot);
		if (i < j)
			swap(list[i], list[j]);
	}
	swap(list[j], list[l]);
	return j;
}

void QuickSort(vector<int>& data, int l, int r)
{
	if (l + 1 < r)
	{
		int j = Partition(data, l, r);
		QuickSort(data, l, j);
		QuickSort(data, j + 1, r);
	}
}

int main(void)
{
	srand(time(0));
	int N, num;
	cin >> N;
	vector<int> data;
	data.reserve(N + 1);
	for (int i = 0; i < N; i++)
	{
		cin >> num;
		data.push_back(num);
	}
	data.push_back(1e9 + 7);
	QuickSort(data, 0, N);
	cout << data[0];
	for (vector<int>::const_iterator it = data.begin() + 1; it != data.end() - 1; it++)
	{
		cout << ' ' << *it;
	}
	cout << endl;
}

#endif