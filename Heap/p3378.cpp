#ifdef RUN_P3378
#include <vector>
#include <iostream>
#include <functional>
using namespace std;

template<typename T>
class my_priority_queue
{
public:
	vector<T> m_data;
	function<bool(T, T)> m_predicate;
	unsigned int last_index;
	my_priority_queue(function<bool(T, T)> predicate);
	my_priority_queue(vector<T>& data, function<bool(T, T)> predicate);
};


//将需要调整的元素不断下沉直至不需要再下沉或者下沉到leaf_node
template<typename T>
void heapify_down(vector<T>& data, function<bool(T, T)> predicate, int index, int last_index)
{
	bool need_to_continue_heapify = true;
// 根据传入的两个索引判断那个数据优先级更高，注意传入的left和right的顺序，
// predicate判断的是第一个参数优先级是否高于第二个，是则返回true，否则返回false
	auto returnindexwithprio = [predicate, &data](int left, int right) 
		{
		if (predicate(data[left], data[right]))
			return left;
		return right;
		};
// 循环继续的两个条件：
// 1.有left_child(如果left_child都没有肯定没有right_child)
// 2.上一次发生了交换，如果在某一轮循环没发生交换说明堆调整完毕
	while (2 * index <= last_index && need_to_continue_heapify)
	{
		//判断是否有right_child，如果没有则进入只判断是否和left_child交换的分支
		if (2 * index + 1 <= last_index)
		{
			//存储right/left_child中有更高优先级的child的索引
			int higher_prio = returnindexwithprio(2 * index, 2 * index + 1);
			//判断是否需要和有更高优先级的child交换，注意顺序：更高优先级的child交换在第一个参数
			//predicate判断的是第一个参数优先级是否高于第二个,在priority_queue中优先级高的在堆顶
			//所以下面的意思就是"如果位于下面的有更高优先级的child具有比当前在进行heapify_down的数据更高的优先级，就互换"
			if (predicate(data[higher_prio], data[index]))
			{
				swap<T>(data[higher_prio], data[index]);
				index = higher_prio;//别忘了在交换后更新位置
				continue;
			}
		}
		else if (predicate(data[2 * index], data[index]))
		{
			swap<T>(data[2 * index], data[index]);
			index *= 2;//别忘了在交换后更新位置
			continue;
		}
		need_to_continue_heapify = false;//如果在上面未发生交换，则设置标志变量为false
	}
}


template<typename T>
my_priority_queue<T>::my_priority_queue(function<bool(T, T)> predicate)
	: m_predicate(predicate), last_index(0) 
{
	m_data.push_back(T());//数组表示的heap的index从1开始，所以往index = 0处随便填充一个，记得类T要有默认构造函数
}

template<>
my_priority_queue<int>::my_priority_queue(function<bool(int, int)> predicate)
	: m_predicate(predicate), last_index(0)
{
	m_data.push_back(0);
}

template<typename T>
my_priority_queue<T>::my_priority_queue(vector<T>& data, function<bool(T, T)> predicate)//根据传入的数据建堆
	: m_predicate(predicate)
{
	m_data.push_back(T());
	for (auto i : data)
	{
		m_data.emplace_back(i);
	}
	last_index = m_data.size() - 1;
	//从后向前遍历数组，依次调用heapify_down函数来调整堆
	for (int i = last_index; i >= 1; i--)
	{
		heapify_down<T>(m_data, m_predicate, i, last_index);
	}
}

template<>
my_priority_queue<int>::my_priority_queue(vector<int>& data, function<bool(int, int)> predicate)
	: m_predicate(predicate)
{
	m_data.push_back(0);
	for (int i : data)
	{
		m_data.push_back(i);
	}
	last_index = m_data.size() - 1;
	for (int i = last_index; i >= 1; i--)
	{
		heapify_down<int>(m_data, m_predicate, i, last_index);
	}
}

//将插入的数据不断上浮直至不需要再上浮或者已经上浮到堆顶
template<typename T>
void my_insert(my_priority_queue<T>& target, T data)
{
	//现将数据插入到数组末尾，即在堆的最后一个位置后面再开一个
	target.m_data.push_back(data);
	auto predicate = target.m_predicate;
	//相当于存储需要进行上浮操作的数据的位置
	int index = ++target.last_index;
	while (predicate(target.m_data[index], target.m_data[index / 2]) && index > 1)
	{
		swap(target.m_data[index], target.m_data[index / 2]);
		index /= 2;//别忘了在交换后更新位置
	}
}

template<typename T>
void my_delete(my_priority_queue<T>& target)
{
	target.m_data[1] = target.m_data[target.last_index];//先用堆为的数据覆盖堆顶，相当于删除堆顶的元素
	target.m_data.pop_back();//堆尾的数据已经放在堆顶，现移除堆尾元素
	target.last_index--;
	heapify_down<T>(target.m_data, target.m_predicate, 1, target.last_index);//对堆顶元素进行heapify_down以调整堆
}

template<typename T>
void showtop(my_priority_queue<T>& target)
{
	if(target.m_data.size() > 1)
		cout << target.m_data[1] << endl;
}


int main(void)
{
	vector<int> data = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	my_priority_queue<int> list(data, greater<int>());
	//my_delete(list);
	//my_priority_queue<int> list{ greater<int>() };
	//my_insert<int>(list, 5);
	//my_insert<int>(list, 3);
	//my_insert<int>(list, 7);
	//my_insert<int>(list, 6);
	//my_insert<int>(list, 11);
	//my_insert<int>(list, 4);
	/*my_insert<int>(list, 18);*/
	
	for (int i : list.m_data)
	{
		cout << i << endl;
	}
	
}
#endif


//更改上面普通版构造函数,见更改提醒
























