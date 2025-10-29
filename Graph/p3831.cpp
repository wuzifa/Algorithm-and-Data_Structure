//图中需要包含的信息:
//时间信息，能否到达终点的信息
//首先如果换乘点都无法到达终点，其余普通节点更没法到达终点
//其次在上面一条的前提下，仅仅包含换乘点已经雨涵了所有需要的时间信息，站点间可以通过计算坐标得出时间
//换成站点间有换乘时间，所以需要换乘站点
#ifdef RUN_P3831
#include <vector>
#include <iostream>
#include <algorithm>
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
				swap(data[higher_prio], data[index]);
				index = higher_prio;//别忘了在交换后更新位置
				continue;
			}
		}
		else if (predicate(data[2 * index], data[index]))
		{
			swap(data[2 * index], data[index]);
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

//将插入的数据不断上浮直至不需要再上浮或者已经上浮到堆顶
template<typename T>
void my_insert(my_priority_queue<T>& target, T data)
{
	//现将数据插入到数组末尾，即在堆的最后一个位置后面再开一个
	target.m_data.push_back(data);
	auto predicate = target.m_predicate;
	//相当于存储需要进行上浮操作的数据的位置
	int index = ++target.last_index;
	while (index > 1 && predicate(target.m_data[index], target.m_data[index / 2]))
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
T& returntop(my_priority_queue<T>& target)
{
	if (target.m_data.size() > 1)
		return target.m_data[1];
}

//=====================上面是优先队列的实现=============================================
struct station
{
	unsigned int x, y;//x, y分别表示这个站点所在行数和列数
	unsigned int index;//index是为了方便后面在邻接矩阵中按行和列建立边，index为这个station对应的行索引
	//定位到这个换乘站的边应该填写在领接矩阵的哪个索引
};
typedef enum 
{
	EXCHANGE, HOME
}kind;
struct graph_node
{
	kind node_kind;
	unsigned int index;
	unsigned int distance;
	bool selected;
	graph_node()
		:distance(4294967295), node_kind(EXCHANGE), index(0), selected(false){}
	
};



typedef enum 
{
	X, Y
}xory;

template<xory strategy>
struct comparestation_coor_ascend
{
	bool operator()(station* l, station* r)
	{
		if (strategy == X)
			return l->x < r->x;

		return l->y < r->y;
	}
};
//第一个存点索引，第二个存点的distance
typedef pair<unsigned int, unsigned int> node_info;
int dijkstra(vector<graph_node*>& map, vector<vector<pair<unsigned int, unsigned int>>>& adj)
{
	map[map.size() - 3]->distance = map[map.size() - 4]->distance = 0;
	map[map.size() - 1]->node_kind = map[map.size() - 2]->node_kind = HOME;
	auto func = [](node_info a, node_info b)
		{
			return a.second < b.second;
		};
	my_priority_queue<node_info> list{ func };
	my_insert<node_info>(list, make_pair(map.size() - 3, 0));
	my_insert<node_info>(list, make_pair(map.size() - 4, 0));
	//unsigned int graph_size = map.size();
	while (list.m_data.size() > 1)
	{
		node_info now_select = returntop(list);
		my_delete<node_info>(list);
		if (map[now_select.first]->node_kind == HOME)
			return now_select.second;
		if (now_select.second > map[now_select.first]->distance)
			continue;
		for (pair<unsigned int, unsigned int>& connected_node : adj[now_select.first])
		{
			if (!map[connected_node.first]->selected)
			{
				if (now_select.second + connected_node.second < map[connected_node.first]->distance)
				{
					my_insert<node_info>(list, make_pair(connected_node.first, now_select.second + connected_node.second));
					map[connected_node.first]->distance = now_select.second + connected_node.second;
				}
			}
		}
		map[now_select.first]->selected = true;
	}
	return -1;
}
int main(void)
{
	unsigned int width, exchange_num;
	cin >> width >> exchange_num;
	station* info = new station[exchange_num + 2];
	//第一个存索引，第二个存边的权
	vector<vector<pair<unsigned int, unsigned int>>> adj;
	vector<vector<station*>> row, column;
	//起点，终点，换乘点两两一对，索引中小的代表行，大的代表列
	//graph.resize(2*(exchange_num + 2));
	adj.resize((exchange_num + 2) * 2);
	row.resize(width + 1); column.resize(width + 1);
	unsigned int x, y;
	for (unsigned int i = 0; i < exchange_num + 2; i++)
	{
		cin >> x >> y;
		info[i].x = x;
		row[x].push_back(&info[i]);
		info[i].y = y;
		column[y].push_back(&info[i]);
		info[i].index = i * 2;
	}
	
	for (int i = 1, size = row.size(); i < size; i++)
	{
		sort(row[i].begin(), row[i].end(), comparestation_coor_ascend<Y>());
		sort(column[i].begin(), column[i].end(), comparestation_coor_ascend<X>());
	}
	unsigned int last_index_exstation = adj.size() - 3;
	for (unsigned int i = 0; i <= last_index_exstation; i += 2)
	{
		adj[i].emplace_back(i + 1, 1);
		adj[i + 1].emplace_back(i, 1);
	}
	for (unsigned int i = 1, size = row.size(); i < size; i++)
	{
		if(!row[i].empty())
			for (vector<station*>::const_iterator it = row[i].begin(); it != row[i].end() - 1; it++)
			{
				adj[(*it)->index].emplace_back((*(it + 1))->index, ((*(it + 1))->y - (*it)->y) * 2);
				adj[(*(it + 1))->index].emplace_back((*it)->index, ((*(it + 1))->y - (*it)->y) * 2);
			}
		if(!column[i].empty())
			for (vector<station*>::const_iterator it = column[i].begin(); it != column[i].end() - 1; it++)
			{
				//unsigned int a = (*it)->index + 1, b = (*(it + 1))->index + 1;
				//graph[a][b] = graph[b][a] = ((*(it + 1))->x - (*it)->x) * 2;
				adj[(*it)->index + 1].emplace_back((*(it + 1))->index + 1, ((*(it + 1))->x - (*it)->x) * 2);
				adj[(*(it + 1))->index + 1].emplace_back((*it)->index + 1, ((*(it + 1))->x - (*it)->x) * 2);
			}
	}
	//graph_node* map = new graph_node[graph.size()];//这个数组的索引和graph中的索引对应
	vector<graph_node*> map;
	map.resize(adj.size());
	//for (graph_node*& i : map)
	//	i = new graph_node;
	for (unsigned int i = 0, map_size = map.size(); i < map_size; i++)
	{
		map[i] = new graph_node();
		map[i]->index = i;
	}
	cout << dijkstra(map, adj);




	return 0;
}

#endif

//在应对就条目的更新逻辑有问题，超时没了，结果变成错误答案了
//把邻接矩阵改成邻接表图中点很多但是边很少(稀疏图用邻接表，否则占用太多内存)
//在提交前把ininfo数组在建立好邻接表后删掉，row和column也删掉