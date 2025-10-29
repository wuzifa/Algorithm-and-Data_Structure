
#ifdef RUN_FENWICK
#include <iostream>
#include <vector>



using namespace std;


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
	: m_tree(data), m_size(data.size())//data.size()必须正好等于实际数据数量
{
	int parent;
	for (unsigned int i = 1; i < m_size; i++)
	{
		parent = i + LSB(i);
		if(parent < m_size)
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

//原数组：[2, 5, 3, 7, 4]
//差分数组：[2, 3, -2, 4, -3]
//将区间：[5, 3, 7]每个加2
//新差分数组：[2, 5, -2, 4, -5]
//原数组区间：[l, r]中每个元素加k(k可为负数)
//差分数组变化：dif[l] += k, dif[r + 1] -= k
//要查询原数第i个位置的值，对差分数组求前缀和求到i即可





#endif