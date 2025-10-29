#ifdef RUN_P1886
#include <iostream>
#include <deque>
#include <vector>
using namespace std;

struct node
{
	int m_value;
	unsigned int m_pos;
	node(int value, unsigned int pos)
		:m_value(value), m_pos(pos) {}
};

void init_window_descend(deque<node>& window, vector<int>& data, unsigned int window_lengtrh)
{
	for(unsigned int i = 1; i <= window_lengtrh; i++)
	{
		while (!window.empty() && window.back().m_value < data[i])
		{
			window.pop_back();
		}
		window.emplace_back(data[i], i);
	}
}

void move_window_large(deque<node>& window, vector<int>& data, unsigned int window_lengtrh, unsigned int data_length)
{
	unsigned int last_window_pos = data_length - window_lengtrh + 1;
	for (unsigned int i = 2; i <= last_window_pos; i++)
	{
		if (window.front().m_pos < i)
			window.pop_front();
		int new_data = data[i + window_lengtrh - 1];
		while (!window.empty() && window.back().m_value < new_data)
		{
			window.pop_back();
		}
		window.emplace_back(new_data, i + window_lengtrh - 1);
		cout << window.front().m_value << ' ';
	}
}

void init_window_ascend(deque<node>& window, vector<int>& data, unsigned int window_lengtrh)
{
	for (unsigned int i = 1; i <= window_lengtrh; i++)
	{
		while (!window.empty() && window.back().m_value > data[i])
		{
			window.pop_back();
		}
		window.emplace_back(data[i], i);
	}
}

void move_window_small(deque<node>& window, vector<int>& data, unsigned int window_lengtrh, unsigned int data_length)
{
	unsigned int last_window_pos = data_length - window_lengtrh + 1;
	for (unsigned int i = 2; i <= last_window_pos; i++)
	{
		if (window.front().m_pos < i)
			window.pop_front();
		int new_data = data[i + window_lengtrh - 1];
		while (!window.empty() && window.back().m_value > new_data)
		{
			window.pop_back();
		}
		window.emplace_back(new_data, i + window_lengtrh - 1);
		cout << window.front().m_value << ' ';
	}
}
int main(void)
{
	vector<int> data;
	deque<node> window;
	unsigned int data_length, window_length;
	cin >> data_length >> window_length;
	data.resize(data_length + 10);
	for (unsigned int i = 1; i <= data_length; i++)
		cin >> data[i];
	init_window_ascend(window, data, window_length);
	cout << window.front().m_value << ' ';
	move_window_small(window, data, window_length, data_length);
	window.clear();
	cout << endl;
	init_window_descend(window, data, window_length);
	cout << window.front().m_value << ' ';
	move_window_large(window, data, window_length, data_length);
}












#endif