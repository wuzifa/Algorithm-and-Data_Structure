#ifdef	RUN_B4016
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//求树(无向无环图)的直径

//邻接表
vector<vector<int>> adj;
//(选定从哪个节点开始进行dp递归后)表示以某个节点作为root时这个子树的最长链是多少,记忆化递归
vector<int> subtree_chain;

//递归解决当index == root的节点作为根节点时子树的最长链(其实就是树的最大深度)是多少
int Subtree_chain(int root, int parent)
{
	//如果是leaf_node
	if (adj[root].size() == 1)
		return 0;
	//如果这个节点第二次被这个递归函数调用到
	if (subtree_chain[root] != -10)
		return subtree_chain[root];
	int maxsubtreechain = -10;
	for (int child : adj[root])
	{
		//防止parent node调用这个递归函数求child_node的最大深度，结果child_node又调用这个递归函数求parent_node的最大深度，陷入死循环
		if (child == parent)
			continue;
		int new_chain = Subtree_chain(child, root);
		//将递归得到的结果记入表中
		subtree_chain[child] = new_chain;
		//得到所有子树中深度最大的
		if (new_chain > maxsubtreechain)
			maxsubtreechain = new_chain;
	}
	return maxsubtreechain + 1;
}

//这个Diameter函数不像上面那个递归函数不会对一个节点重复调用，对每个节点只调用一次，所以不用加记忆化
//对每个节点都有两种情况: 最大直径经过还是不经过当前节点，也相当于是一种"try all possibilities"
int Diameter(int root, int parent)
{
//>>>>>>>>>>>>

	//"adj[root].size() == 1"判断当前节点是否为根节点
	if (adj[root][0] == parent && adj[root].size() == 1)
		return 0;
	vector<int> subtreechain;
	//防止这个节点的子节点数不够两个
	subtreechain.insert(subtreechain.begin(), 2, -1);
	//求每个子节点作为根节点时的最大链长
	for (int child : adj[root])
	{
		//不要去求parent_node的最长链，这里应该只求child_node的最长链
		if (child == parent)
			continue;
		subtreechain.push_back(Subtree_chain(child, root));
	}
	std::nth_element(subtreechain.begin(), subtreechain.begin() + 1, subtreechain.end(), std::greater<int>());

//<<<<<<<<<<<<<上面是情况1: 直径经过当前root节点      ==================      >>>>>>>>>>>>>>>下面是情况2: 直径不经过当前节点

	int max_subtree_diameter = -10;
	//求每个子节点作为根时的子树的的diameter
	for (int child : adj[root])
	{
		//跟上面Subtree_chain函数一样，防止陷入死循环
		if (child == parent)
			continue;
		int newdia = Diameter(child, root);
		if (newdia > max_subtree_diameter)
			max_subtree_diameter = newdia;
	}

//<<<<<<<<<<<<<<<<<<<<   ====================
	//返回两种情况中的较大值
	return max(subtreechain[0] + subtreechain[1] + 2, max_subtree_diameter);
}






int main(void)
{
	int node_num, a, b, start;
	cin >> node_num;
	adj.resize(node_num + 1);
	subtree_chain.resize(node_num + 1, -10);
	while (--node_num)
	{
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	//这个start表示递归起点，可以选择图中任意存在的点
	start = 1;
	cout << Diameter(start, -10) << endl;
	
}








#endif