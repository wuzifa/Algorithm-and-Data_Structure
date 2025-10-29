#ifdef RUN_GROUPFILE54
#include <iostream>
#include <vector>
using namespace std;

int main(void)
{ 
	int num;//输入的数字个数
	cin >> num;
	int data;//接收输入的数字
	vector<int> arr;//存储已存在的数字
	vector<int>::const_iterator it;
	while (num--)
	{
		cin >> data;
		for (it = arr.begin(); it != arr.end(); it++)
		{
			if (*it == data)
				break;
		}
		if (it == arr.end())
		{
			cout << data << ' ';
			arr.push_back(data);
		}
	}
	return 0;
}
#endif
