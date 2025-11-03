#ifdef RUN_P3397
#include <iostream>
#include <vector>
using namespace std;

//树状数组擅长求前缀和，单点修改
//区间修改通过差分数组转换为单点修改(修改差分数组的单点)
//单点查询通过差分数组转换为求前缀和
//地毯就是每次铺个地毯就改(长)个数组的区间
//最后求每个点覆盖的地毯树就是求原数组每个索引处的值，(也就是求差分数组的前缀和)
//综上所述用树状数组维护差分数组的前缀和
class Fenwick_Tree
{
private:
	vector<int> m_tree;//m_trees索引从1开始, m_tree[0]填充默认值
	unsigned int m_size;//表示m_tree这个vector的大小，包括m[0]
	int LSB(int index);
public:
	Fenwick_Tree(vector<int>& data);//传入的data实际数据索引从1开始
	int prefix_sum(int index);
	int range_sum(int l, int r);//返回[l, r]区间内的和
	void add_point(int index, int value);
	void set_point(int index, int value);
};

//找出the value of the least significant bit 
int Fenwick_Tree::LSB(int index)
{
	return index & -index;
}


Fenwick_Tree::Fenwick_Tree(vector<int>& data)
	: m_tree(data), m_size(data.size())
{
	int parent;
	for (unsigned int i = 1; i < m_size; i++)
	{
		parent = i + LSB(i);
		if (parent < m_size)
			m_tree[parent] += m_tree[i];
	}
}

int Fenwick_Tree::prefix_sum(int index)
{
	int sum = 0;
	while (index > 0)
	{
		sum += m_tree[index];
		index &= ~LSB(index);
		//上面这句相当于index -= LSB(index)
	}
	return sum;
}

int Fenwick_Tree::range_sum(int l, int r)
{
	return prefix_sum(r) - prefix_sum(l - 1);
}

void Fenwick_Tree::add_point(int index, int value)
{
	while (index < m_size)
	{
		m_tree[index] += value;
		index += LSB(index);
	}
}

void Fenwick_Tree::set_point(int index, int value)
{
	add_point(index, value - m_tree[index]);
}

int main(void)
{
	vector<Fenwick_Tree> diff;
	
	int n, carpet_num;
	cin >> n >> carpet_num;
	diff.reserve(n + 1);
	
	vector<int> fill(n + 1, 0);
	for (int i = 0; i < n + 1; i++)
	{
		diff.emplace_back(fill);
	}
	int x1, y1, x2, y2;
	for(int i = 0; i < carpet_num; i++)
	{
		cin >> y1 >> x1 >> y2 >> x2;
		for (int y = y1; y <= y2; y++)
		{
			diff[y].add_point(x1, 1);
			diff[y].add_point(x2 + 1, -1);
		}
	}
	for (int row = 1; row <= n; row++)
	{
		for (int i = 1; i <= n; i++)
			cout << diff[row].prefix_sum(i) << ' ';
		cout << endl;
	}
}
#endif