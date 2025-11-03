#ifdef RUN_P3369
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>

using namespace std;

// 二叉搜索树在增删树一般用的递归模式都像这样:
// 先判断要增/删的元素v是小于还是大于当前节点(root)的元素
//        小于: root->left = insert/delete(root->left, v)
//		  大于: root->right = insert/delete(root->right, v)
// insert/delete函数原型解析:
// 第一个参数root是为了判断当前节点元素与v的大小关系，是否到达空节点(没找到元素)，
// 在平衡二叉树还需要传给更新函数和平衡函数对当前子树作出相应更改

// 无论是普通二叉树的插入，删除函数还是平衡二叉树的更新，平衡函数，都一个相同的模式：
// 将可能更改的子树的根节点传给函数，函数对这个子树作出相应改动后再把改动完的子树的根节点通过函数返回值传回去
// 这样就完成了对这个子树的更改
template <typename T>
struct node
{
	T m_value;
	int8_t balance_factor;
	int subtree_height, subtree_elenum;
	int left_child, right_child, m_parent;
	unsigned int count;
	node(T& value, int parent);
};

template <typename T>
node<T>::node(T& value, int parent)
	: m_value(value), 
	  left_child(-1), right_child(-1), m_parent(parent),
	  count(1), balance_factor(0),
	  subtree_height(0), subtree_elenum(1) {}

template<typename T>
class AVL_Tree
{
public:
	vector<node<T>> m_tree;
	unsigned int m_size;
	unsigned int insertion_place;
	unsigned int m_root;
	vector<unsigned int> vacant_place;
public:
	AVL_Tree();
	int insert(int root, T& data, int parent);
	int remove(int root, T& data);
	T k_th(int root, int k);
	int querysmaller_num(T& data, unsigned int& sum);
	int querybigger_num(T& data, unsigned int& sum);
	pair<T, int> mininsubtree(int root);
	T maxinsubtree(int root);
	void update(int root);
	int balance(int root);
	int rightrotate(int root);
	int leftrotate(int root);
	int queryforward(T& data);
	int querybackward(T& data);
};

template<typename T>
int AVL_Tree<T>::querybackward(T& data)
{
	int pos = m_root, min_num = -100;
	while (pos != -1)
	{
		if (data <= m_tree[pos].m_value)
		{
			if (data != m_tree[pos].m_value)
				min_num = m_tree[pos].m_value;
			else if (m_tree[pos].right_child != -1)
				min_num = mininsubtree(m_tree[pos].right_child).first;

			pos = m_tree[pos].left_child;
		}
		else
			pos = m_tree[pos].right_child;
	}
	return min_num;
}

template<typename T>
int AVL_Tree<T>::queryforward(T& data)
{
	int pos = m_root, max_num = -100;
	while (pos != -1)
	{
		if (data >= m_tree[pos].m_value)
		{
			if (data != m_tree[pos].m_value)
				max_num = m_tree[pos].m_value;
			else if(m_tree[pos].left_child != -1)
				max_num = maxinsubtree(m_tree[pos].left_child);
			
			pos = m_tree[pos].right_child;
		}
		else
			pos = m_tree[pos].left_child;
	}
	return max_num;
}

template<typename T>
int AVL_Tree<T>::leftrotate(int root)
{
	/*int parent;
	if (root == m_root)
		parent = m_tree[root].m_parent;
	else
		parent = -1;*/
	int parent = m_tree[root].m_parent;
	int temp = m_tree[root].right_child;
	if (temp != -1)
	{
		m_tree[root].right_child = m_tree[temp].left_child;
		if (m_tree[temp].left_child != -1)
			m_tree[m_tree[temp].left_child].m_parent = root;
		m_tree[temp].left_child = root;
		m_tree[root].m_parent = temp;
		m_tree[temp].m_parent = parent;
	}
	//注意顺序
	update(root);
	update(temp);
	return temp;
}

template<typename T>
int AVL_Tree<T>::rightrotate(int root)
{
	
	/*if (root == m_root)
		parent = m_tree[root].m_parent;
	else
		parent = -1;*/
	int parent = m_tree[root].m_parent;
	int temp = m_tree[root].left_child;
	if (temp != -1)
	{
		m_tree[root].left_child = m_tree[temp].right_child;
		if (m_tree[temp].right_child != -1)
			m_tree[m_tree[temp].right_child].m_parent = root;
		m_tree[temp].right_child = root;
		m_tree[root].m_parent = temp;
		m_tree[temp].m_parent = parent;
	}
	//注意顺序：旋转后root成为temp的child，先update child，再update parent
	update(root);
	update(temp);
	return temp;
}

template<typename T>
int AVL_Tree<T>::balance(int root)
{
	if (m_tree[root].balance_factor == -2)
	{
		if (m_tree[m_tree[root].left_child].balance_factor > 0)
			m_tree[root].left_child = leftrotate(m_tree[root].left_child);
			
		root = rightrotate(root);
	}
	else if (m_tree[root].balance_factor == 2)
	{
		if (m_tree[m_tree[root].right_child].balance_factor < 0)
			m_tree[root].right_child = rightrotate(m_tree[root].right_child);
			
		root = leftrotate(root);
	}
	return root;
}

template<typename T>
void AVL_Tree<T>::update(int root)
{
	int leftsubtree_height, rightsubtree_height, l_subtree_elenum, r_subtree_elenum;
	if (m_tree[root].left_child != -1)
	{
		leftsubtree_height = m_tree[m_tree[root].left_child].subtree_height;
		l_subtree_elenum = m_tree[m_tree[root].left_child].subtree_elenum;
	}
	else
	{
		leftsubtree_height = -1;
		l_subtree_elenum = 0;
	}
	if (m_tree[root].right_child != -1)
	{
		rightsubtree_height = m_tree[m_tree[root].right_child].subtree_height;
		r_subtree_elenum = m_tree[m_tree[root].right_child].subtree_elenum;
	}
	else
	{
		rightsubtree_height = -1;
		r_subtree_elenum = 0;
	}
	m_tree[root].subtree_height = max(leftsubtree_height, rightsubtree_height) + 1;
	m_tree[root].balance_factor = rightsubtree_height - leftsubtree_height;
	m_tree[root].subtree_elenum = m_tree[root].count + l_subtree_elenum + r_subtree_elenum;
}

template<typename T>
T AVL_Tree<T>::maxinsubtree(int root)
{
	while (m_tree[root].right_child != -1)
	{
		root = m_tree[root].right_child;
	}
	return m_tree[root].m_value;
}

template<typename T>
pair<T, int> AVL_Tree<T>::mininsubtree(int root)
{
	while (m_tree[root].left_child != -1)
	{
		root = m_tree[root].left_child;
	}
	return make_pair(m_tree[root].m_value, root);
}

template<typename T>
int AVL_Tree<T>::querysmaller_num(T& data, unsigned int& sum)//sum是外部传进来的累加器，传进来前记得设为0
{
	int root = m_root;
	while (root != -1 && m_tree[root].m_value != data)
	{
		if (data >= m_tree[root].m_value)
		{
			if(m_tree[root].left_child != -1)
				sum += m_tree[m_tree[root].left_child].subtree_elenum;
			if (data != m_tree[root].m_value)
				sum += m_tree[root].count;
			root = m_tree[root].right_child;
		}
		else
		{
			root = m_tree[root].left_child;
		}
	}
	if (root != -1 && m_tree[root].left_child != -1)
		sum += m_tree[m_tree[root].left_child].subtree_elenum;
	//do
	//{
	//	if (data >= m_tree[root].m_value)
	//	{
	//		sum += m_tree[m_tree[root].left_child].subtree_elenum;
	//		root = m_tree[root].right_child;
	//	}
	//	else
	//	{
	//		root = m_tree[root].left_child;
	//	}
	//} while (m_tree[root].m_value != data);
	return sum;
}

template<typename T>
int AVL_Tree<T>::querybigger_num(T& data, unsigned int& sum)
{

}

//每个节点的subtree_elenum表示这个节点作为根节点是子树内总元素个数
//假设当前在节点为root的子树，查找这个子树内从小到大排名第k个元素
//(1).k < root->left.subtree_elenum：答案在左子树(还是去左子树查找第k小元素)，return k_th(root->left, k)
//(2).k > root->left.subtree_elenum：
//			若k <= root->left.subtree_elenum + root.count：当前节点就是答案
//			否则答案在右子树(去右子树查找第(k - root->left.subtree_elenum - root.count)个元素，
//			因为在整个子树中去掉了刚才的左子树和刚才的节点,这个数的排名在左子树中和在整个树中时不同的)：return k_th(root->right, k - root->left.subtree_elenum - root.count)
template<typename T>
T AVL_Tree<T>::k_th(int root, int k)
{
	if (m_tree[root].left_child == -1 && m_tree[root].right_child == -1)
		return m_tree[root].m_value;
	int lsubnum = (m_tree[root].left_child != -1) ? m_tree[m_tree[root].left_child].subtree_elenum : 0;
	if (k <= lsubnum)
		return k_th(m_tree[root].left_child, k);
	else
	{
		if (k <= lsubnum + m_tree[root].count)
			return m_tree[root].m_value;
		else
			return k_th(m_tree[root].right_child, k - (lsubnum + m_tree[root].count));
	}
}

template<typename T>
int AVL_Tree<T>::remove(int root, T& data)
{
	if (root == -1)
		return root;
	else if (data < m_tree[root].m_value)
		m_tree[root].left_child = remove(m_tree[root].left_child, data);
	else if(data > m_tree[root].m_value)
		m_tree[root].right_child = remove(m_tree[root].right_child, data);
	else
	{
		if (--m_tree[root].count)
		{
			m_tree[root].subtree_elenum--;
			//这种情况对子树的更改只改了subtree_elenum,上面直接手动改了，不用再调一遍递归
			return root;
		}
		else if (m_tree[root].left_child == -1 && m_tree[root].right_child == -1)
		{
			vacant_place.push_back(root);
			root = -1;
			//early out,不然update m_tree[-1]
			return root;
		}
		
		else if (m_tree[root].left_child == -1)
		{
			vacant_place.push_back(root);
			root = m_tree[root].right_child;
			return root;
		}
		else if (m_tree[root].right_child == -1)
		{
			vacant_place.push_back(root);
			root = m_tree[root].left_child;
			return root;
		}
		else
		{
			auto res = mininsubtree(m_tree[root].right_child);
			m_tree[root].m_value = res.first;
			m_tree[root].count = m_tree[res.second].count;
			m_tree[root].right_child = remove(m_tree[root].right_child, res.first);
		}
	}
	update(root);
	root = balance(root);
	return root;
}

template<typename T>
int AVL_Tree<T>::insert(int root, T& data, int parent)
{
	if (insertion_place == 0)
	{
		m_tree.emplace_back(data, -1);
		m_size++;
		return insertion_place++;
	}
	
	if (root == -1)
	{
		if (!vacant_place.empty())
		{
			int freeplace = vacant_place.back();
			vacant_place.pop_back();
			m_tree[freeplace] = node<T>(data, parent);
			m_size++;
			return freeplace;
		}
		m_tree.emplace_back(data, parent);
		m_size++;
		return insertion_place++;
	}

	if (data == m_tree[root].m_value)
	{
		m_tree[root].count++;
		m_tree[root].subtree_elenum++;
	}
	else if (data < m_tree[root].m_value)
		m_tree[root].left_child = insert(m_tree[root].left_child, data, root);
	else
		m_tree[root].right_child = insert(m_tree[root].right_child, data, root);
	update(root);
	return balance(root);
}

template<typename T>
AVL_Tree<T>::AVL_Tree()
	: m_size(0), insertion_place(0), m_root(0) {}

int main(void)
{
	//#ifndef ONLINE_JUDGE
	//	freopen("C:/Users/wuzif/source/repos/everyday_homework/testdata/P3369_1.in", "r", stdin);
	//	freopen("C:/Users/wuzif/source/repos/everyday_homework/testdata/P3369_1.out", "w", stdout);
	//#endif
	AVL_Tree<int> test;
	int operation_num, operation, data, k;
	unsigned int sum;
	cin >> operation_num;
	while (operation_num--)
	{
		cin >> operation;
		switch (operation)
		{
		case 1:
			cin >> data;
			test.m_root = test.insert(test.m_root, data, -1);
			break;
		case 2:
			cin >> data;
			test.m_root = test.remove(test.m_root, data);
			break;
		case 3:
			cin >> data;
			sum = 0;
			cout << test.querysmaller_num(data, sum) + 1 << endl;//应该没问题了
			break;
		case 4:
			cin >> k;
			cout << test.k_th(test.m_root, k) << endl;
			break;
		case 5:
			cin >> data;
			cout << test.queryforward(data) << endl;
			break;
		case 6:
			cin >> data;
			cout << test.querybackward(data) << endl;
			break;
		default:
			break;
		}
	}
	return 0;
}


#endif