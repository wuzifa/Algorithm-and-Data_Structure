#ifdef RUN_P2097
#include <iostream>
#include <vector>
using namespace std;

// 可以看作图的数组
// 两个主要功能:
// 1.高效返回每个元素所属的group
// 2.高效进行merge操作(将两个group合并)

class Union_Find
{
public:
// m_pointer存储下标对应obj的parent_node坐标，相当于用数组模拟指针，m_groupsize存储每个节点作为root node时其group内节点数量
// m_groupsize为0表示这个节点有parent node，为1表示这个节点为孤立节点，其余值表示这个节点为root节点，这个值为它内部的元素个数
	vector<int> m_pointer, m_groupsize;
// m_size为并查集内部元素个数，m_groupnum为并查集内部group个数
	unsigned int m_size, m_groupnum;
	Union_Find(int num);
	unsigned int find(unsigned int index);
	void unify(int index_1, int index_2);
	unsigned int groupsize(unsigned int index);
	bool samegroup(unsigned int index_1, unsigned int index_2);
};

// 初始化逻辑：将每个独立元素视作一个group,元素自己的"parent指针"指向自己，自己就是root node
Union_Find::Union_Find(int num)
	: m_size(num), m_groupnum(num), m_groupsize(num, 1)
{
	for (int i = 0; i < num; i++)
		m_pointer.push_back(i);
}

unsigned int Union_Find::find(unsigned int index)
{
	//存储在寻找root node路径上所有需要调整m_pointer的obj对应的缩索引
	//(其实find中的路径压缩几乎没派上用场，见下面unify说明)
	vector<int> nodetobeadjusted_index;
	//当找到"pointer"指向自己的node时说明找到root node了，此时退出循环则index表示root node所在索引
	while (m_pointer[index] != index)
	{
		//将路径上所有非root node节点全部放进nodetobeadjusted_index数组，后续一次性将这些节点的"parent指针"指向root node
		nodetobeadjusted_index.push_back(index);
		index = m_pointer[index];
	}
	for (int i : nodetobeadjusted_index)
		m_pointer[i] = index;
	return index;
}

void Union_Find::unify(int index_1, int index_2)
{
	unsigned int root1 = find(index_1);
	unsigned int root2 = find(index_2);
	//如果index_1和index_2的root node不同，进入下面merge操作分支
	if (root1 != root2)
	{
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//这里的判断对维持并查集不出现长链结构非常重要，几乎就这里一个判断就实现了路径压缩的全部效果
		//这里让groupsize小的root指向groupsize大的root:
		//1.在merge操作时保证很少出现a -> b ->c -> ...这样的结构，也变向保证并查集中不会出现环状结构
		//大部分的结构都类似：
		// a -> b <- c
		//      ↑
		//      d
		//2.在两个大group进行merge时不可避免出现链式结构时也能确保链的数量少一点，因为被合并的root node那块分支才会出现链式结构
		if(m_groupsize[root1] < m_groupsize[root2])
		{
			m_pointer[root1] = root2;//将groupsize大的root作为groupsize小的root的parenf node
			m_groupsize[root2] += m_groupsize[root1];
			m_groupsize[root1] = 0;
			m_pointer[index_1] = root2;
		}
		else
		{
			m_pointer[root2] = root1;
			m_groupsize[root1] += m_groupsize[root2];
			m_groupsize[root2] = 0;
			m_pointer[index_2] = root1;
		}
		m_groupnum--;//进行了unify操作则两个不同的group合二为一，所以group数量--
	}
}

unsigned int Union_Find::groupsize(unsigned int index)
{
	return m_groupsize[find(index)];
}

bool Union_Find::samegroup(unsigned int index_1, unsigned int index_2)
{
	return find(index_1) == find(index_2);
}
//=====================================================

int main(void)
{
	Union_Find uf(6);

	// 构造一条长链
	uf.unify(0, 1);
	uf.unify(1, 2);
	uf.unify(2, 3);
	uf.unify(3, 4);
	uf.unify(4, 5);

	// 调用 find 多次观察路径压缩
	uf.find(5);
	for (int i = 0; i < 6; ++i)
		std::cout << uf.find(i) << " ";
	std::cout << "\n";

}

#endif