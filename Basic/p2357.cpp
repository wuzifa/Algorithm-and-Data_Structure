
#ifdef RUN_P2357
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
	long long prefix_sum(int index);
	long long range_sum(int l, int r);//返回[l, r]区间内的和
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
		if (parent < m_size)
			m_tree[parent] += m_tree[i];
	}
}

long long Fenwick_Tree::prefix_sum(int index)
{
	long long sum = 0;
	while (index > 0)
	{
		sum += m_tree[index];
		index &= ~LSB(index);
		//上面这句相当于index -= LSB(index)
	}
	return sum;
}

long long Fenwick_Tree::range_sum(int l, int r)
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


// 维护两个数组，一个就是普通的原始数组的差分数组d[i]，原始数组为墓碑风水值
// 另一个为辅助数组Aⁿ，其中Aⁱ = i * (value of 普通差分数组at index i)
// 当进行区间更新时两个数组的树状数组都要进行点更新，因为在求原始数组的区间和时要求上面两个数组的前缀和
// 在更新区间时某个d[i]会发生改变，而上面两个数组都包含d[i]，所以两个都要更新
// 具体求原始数组的区间和的公式见链接:   【树状数组-区间修改、区间查询-哔哩哔哩】 https://b23.tv/nIR6u2t
int main(void)
{
	int tombstone_num, operation_num;
	vector<int> dif_tombstone;
	vector<int> auxiliary;
	int last_value = 0, now_value;
	cin >> tombstone_num >> operation_num;
	dif_tombstone.push_back(0);
	auxiliary.push_back(0);
	auxiliary.reserve(tombstone_num);
	dif_tombstone.reserve(tombstone_num);
	for (int i = 1; i <= tombstone_num; i++)
	{
		cin >> now_value;
		dif_tombstone.push_back(now_value - last_value);
		auxiliary.push_back(dif_tombstone[i] * i);
		last_value = now_value;
	}
	Fenwick_Tree t1(dif_tombstone);
	Fenwick_Tree t2(auxiliary);
	int operation, addition, l, r;
	while (operation_num--)
	{
		cin >> operation;
		switch (operation)
		{
		case 1:
			cin >> l >> r >> addition;
			t1.add_point(l, addition);
			t1.add_point(r + 1, -addition);
			t2.add_point(l, l * addition);
			t2.add_point(r + 1, -(r + 1) * addition);
			break;
		case 2:
		case 3:
			cin >> addition;
			if (operation == 3)
				addition = -addition;
			// 对原数数组的修改会改变差分数组的值，
			// 对原始数组索引为i增加k,则对应差分数组第i处值 += k,第i + 1处 -= k
			t1.add_point(1, addition);
			t1.add_point(2, -addition);
			t2.add_point(1, 1 * addition);
			t2.add_point(2, -2 * addition);
			break;
		case 4:
			cin >> l >> r;
			cout << ((r + 1) * t1.prefix_sum(r) - t2.prefix_sum(r)) - (l * t1.prefix_sum(l - 1) - t2.prefix_sum(l - 1)) << endl;
			break;
		case 5:
			cout << t1.prefix_sum(1) << endl;
			break;
		default:
			break;
		}
		//for (int i = 1; i <= 5; i++)
		//{
		//	cout << t1.prefix_sum(i) << ' ';
		//}
		//cout << endl;
	}
}

#endif