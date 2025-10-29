//教训：cv的时候看看清楚，老是忘记某个地方改动
//当调试的时候在某一步(箭头所指的哪一行)执行完后发生非预期结果，那一定是这一步的问题，程序不会变魔法


//调试时看的是什么，看的是每一句指令对程序造成了什么影响，黄色箭头表示将要执行的指令，
//摁下f11黄色箭头那句才执行了，此时看监视变量有什么变化，反映出黄色箭头那句对程序的影响
#ifdef RUN_B3642
#include <vector>
#include <iostream>
using namespace std;

vector<pair<int, int>> nodeinfo;//nodeinfo[n].first表示编号为n的节点的left_child信息: 
//0表示left_child为空节点,非0数字表示left_child的编号，即data部分的值
//right_child同理

template<typename datatype = int>
struct node
{
	datatype data;
	node<datatype>* left;
	node<datatype>* right;
};

void buildtree_int(node<int>*& root, int data)//root表示当前子树的root节点，传递指针的引用，直接在函数里修改指针
{
	root = new node<int>;
	root->data = data;
	if (int data_l = nodeinfo[root->data].first)//若当前借调右节点data值不为0(题目规定0表示右节点为空),则构造右子树
		buildtree_int(root->left, data_l);//以引用传入要构造的子树的root节点的，以及它的data成员值
	else
		root->left = nullptr;//这步不能少，表示该left_child子树为空，在遍历二叉树时不要继续遍历
	if(int data_r = nodeinfo[root->data].second)//同上
		buildtree_int(root->right, data_r);//同上
	else
		root->right = nullptr;
}


//前序后序遍历记忆就记相对于那两句递归调用的位置
template<typename datatype>
void preorder_travel(node<datatype>* root)
{
	cout << root->data << " ";//在遍历左子树的递归树展开前打印data值
	if(root->left)
		preorder_travel(root->left);
	if(root->right)
		preorder_travel(root->right);
}

template<typename datatype>
void inorder_travel(node<datatype>* root)
{
	if (root->left)
		inorder_travel(root->left);
	cout << root->data << " ";//在遍历左子树的递归树回缩时并且在访问右子树前打印data值
	if (root->right)
		inorder_travel(root->right);
}

template<typename datatype>
void postorder_travel(node<datatype>* root)
{
	if (root->left)
		postorder_travel(root->left);
	if (root->right)
		postorder_travel(root->right);
	cout << root->data << " ";//在访问完左右子树后才打印data值
}

int main(void)
{
	int nodenum, leftchild_info, rightchild_info;
	cin >> nodenum;
	nodeinfo.reserve(nodenum + 1);
	nodeinfo.emplace_back(0, 0);
	while (nodenum--)
	{
		cin >> leftchild_info >> rightchild_info;
		nodeinfo.emplace_back(leftchild_info, rightchild_info);
	}
	node<int>* tree_root = nullptr;
	//root->data = 1;
	//root->left = root->right = nullptr;
	buildtree_int(tree_root, 1);
	preorder_travel<int>(tree_root);
	cout << endl;
	inorder_travel<int>(tree_root);
	cout << endl;
	postorder_travel<int>(tree_root);
	cout << endl;
}
#endif