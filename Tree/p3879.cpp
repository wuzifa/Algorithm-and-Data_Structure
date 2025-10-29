#ifdef RUN_P3879
#include <iostream>
#include <vector>
#include <bitset>
#include <optional>
using namespace std;

struct letter
{
	bitset<1001> article;
	vector<int> next_node;
	letter();
};

letter::letter()
	: next_node(26, -1) {}

class Trie
{
public:
	unsigned last_node_index;
	vector<letter> m_tree;
	void insert(string& word, short article_index);
	std::optional<bitset<1001>> find_word(string& word);
	Trie();
};

void Trie::insert(string& word, short article_index)
{
	//从字典树头结点开始向下查找，头结点不存有没有作为哪个单词结尾的消息
	//头节点只为了查找第一个字母的索引
	//查找每个节点单词对应的节点是否存在都是从它前面一个单词代表的节点出发查找next_node数组
	unsigned int now_node = 0;
	int next_node;
	//遍历字符串中每个字母
	for (char c : word)
	{
		next_node = m_tree[now_node].next_node[c - 'a'];
		//每一轮判断代表当前字母的节点是否存在
		if (next_node != -1)
			//如果存在，让now_node记录代表当前字母的节点的索引
			//也为了判断下一个字母的节点是否存在
			now_node = next_node;
		else
		{
			m_tree.emplace_back();
			last_node_index++;
			m_tree[now_node].next_node[c - 'a'] = last_node_index;
			now_node = last_node_index;
		}
	}
	//当循环结束时，now_node记录的的是最后一个字母的节点索引
	m_tree[now_node].article.set(article_index);
}



//查找每个节点单词对应的节点是否存在都是从它前面一个单词代表的节点出发查找next_node数组
std::optional<std::bitset<1001>> Trie::find_word(string& word)
{
	unsigned int now_node = 0;
	int next_node;
	bool has_found = true;
	for (char c : word)
	{
		next_node = m_tree[now_node].next_node[c - 'a'];
		if (m_tree[now_node].next_node[c - 'a'] != -1)
			now_node = next_node;
		else
		{
			has_found = false;
			break;
		}
	}
	if (has_found)
		return m_tree[now_node].article;
	
	return nullopt;
}

Trie::Trie()
	: m_tree(1, letter()), last_node_index(0) {}

int main(void)
{
	int article_num, query_num, word_num;
	string word;
	Trie trie;
	cin >> article_num;
	for (int i = 1; i <= article_num; i++)
	{
		cin >> word_num;
		while (word_num--)
		{
			cin >> word;
			trie.insert(word, i);
		}
	}
	cin >> query_num;
	while (query_num--)
	{
		cin >> word;
		auto res = trie.find_word(word);
		if (res)
		{
			bool first = true;
			for (int i = 1; i <= 1000; i++)
			{
				if (res->test(i))
				{
					if (!first)
						cout << ' ';
					cout << i;
					first = false;
				}
			}

		}

		cout << endl;
	}
	
}

#endif