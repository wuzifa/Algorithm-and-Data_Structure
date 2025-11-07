#ifdef RUN_P5788
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// 单调栈：栈内元素维持单调递增或递减

// 每次插入时操作：
// 将当前栈内所有小于要插入的元素全部push_back，即循环做下面这件事：
// "判断当前栈顶元素是否小于(等于，根据题目情况来)要插入的元素，如果是就出栈"，循环做直到栈为空或者遇到比要插入的元素更大的元素

// 解析为什么p5788应该用单调栈：
// 题目背景：给出一列整数序列，要求每个元素后面第一个大于自己的下标
// 1.栈内存的是从右向左遍历整个序列时可能成为当前所处元素A从左向右第一个最大值的candidate
// 当遇见栈中比自己小的元素B时，如果元素A都不是A前面(左边)元素的更大值，那这个元素B更不可能成为比A前面元素更大的candidate
// 2.在每次插入元素A时进行两个操作：
// (1).寻找第一个比A大的元素的下标是多少
// (2).调整candidate stack，为寻找A前面比A大的元素作准备
// 
// 细节问题：
// 1.在这题中如果栈顶元素等于要插入的元素也要出栈，因为栈顶元素等于要插入的元素，
// 如果要插入的元素在将来从右向左遍历时都大于某个数，那当前这个栈顶元素也不会大于那个数
// 2.因为栈没法遍历的特性，所以要在push_back进单调栈前就把需要的答案记录下来



static vector<int> ans;
struct node
{
	int m_value;
	int m_index;
	node(int value, int index);
	bool operator>=(const node& other);
};

node::node(int value, int index)
	: m_value(value), m_index(index) {}

bool node::operator>=(const node& other)
{
	return this->m_value >= other.m_value;
}

//从下向上单调递减的单调栈
template<typename T>
class monotonic_stack
{
public:
	stack<T> m_stack;
	void insert(T data);
};

template<typename T>
void monotonic_stack<T>::insert(T data)
{
	while (!m_stack.empty() && (data >= m_stack.top()))
	{
		m_stack.pop();
	}
	//========下面这段纯粹为了题目写的逻辑不太好，在复用代码的时候删了>>>>>>>>>
	if (m_stack.empty())
		ans.push_back(0);
	else
		ans.push_back(m_stack.top().m_index);
	//<<<<<<<<<<<<<================
	m_stack.push(std::move(data));
}

int main(void)
{
	int data_num, data;
	cin >> data_num;
	stack<int> temp;
	ans.reserve(data_num);
	for (int i = 0; i < data_num; i++)
	{
		cin >> data;
		temp.push(data);
	}
	monotonic_stack<node> test;
	for (int i = data_num; i > 0; i--)
	{
		test.insert(node(temp.top(), i));
		temp.pop();
	}
	reverse(ans.begin(), ans.end());
	for (int i : ans)
		cout << i << ' ';
	cout << endl;
}

#endif