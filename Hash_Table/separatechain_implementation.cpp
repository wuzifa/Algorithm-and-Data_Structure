#include <list>
#include <iostream>
#include <functional>
#include <vector>
using namespace std;

#define DEFAULT_TABLESIZE 1000
#define DEFAULT_LOADFACTOR 5


template<typename K, typename V>
class Entry
{
public:
	K m_key;
	V m_value;
	unsigned int m_hash_value;
	Entry(K key, V value);
	Entry(K key, V value, unsigned int hash_value);
	bool operator==(const Entry<K, V>& other);
	
};

template<typename K, typename V>
Entry<K, V>::Entry(K key, V value, unsigned int hash_value)
	: m_key(key), m_value(value), m_hash_value(hash_value) {}

//判断两个entry的key是否相等
template<typename K, typename V>
bool Entry<K, V>::operator==(const Entry<K, V>& other)
{
	if (this->m_hash_value != other.m_hash_value)
		return false;
	return this->m_key == other.m_key;
}


template<typename K, typename V>
Entry<K, V>::Entry(K key, V value)
	: m_key(key), m_value(value), m_hash_value(std::hash<K>()(m_key)) {}

template<typename K, typename V>
class hash_table_separatechaining
{
public:
	vector<list<Entry<K, V>>> m_table;
	double m_load_factor;
	unsigned int m_ele_num, m_table_size, m_threshold;
	hash_table_separatechaining();
	hash_table_separatechaining(unsigned int table_size, double load_factor);
	void clear();
	bool haskey(K key);
	bool update(Entry<K, V> tobeupdate);
	void insert(Entry<K, V> new_entry);
	pair<bool, V> query(K key);
	pair<bool, pair<K, V>> remove(K key);
	void resizetable();
};

template<typename K, typename V>
bool hash_table_separatechaining<K, V>::update(Entry<K, V> tobeupdate)
{
	size_t bucket_index = std::hash<K>()(tobeupdate.m_key) % m_table_size;
	for (Entry<K, V>& ele : m_table[bucket_index])
	{
		if (ele == tobeupdate)
		{
			ele = tobeupdate;
			return true;
		}
	}
	return false;
}

template<typename K, typename V>
void hash_table_separatechaining<K, V>::resizetable()
{
	vector<list<Entry<K, V>>> new_table;
	m_table_size *= 2;
	new_table.resize(m_table_size);
	size_t bucket_index;
	for (list<Entry<K, V>>& bucket : m_table)
	{
		for (Entry<K, V>& old_entry: bucket)
		{
			bucket_index = old_entry.m_hash_value % m_table_size;
			new_table[bucket_index].emplace_back(old_entry.m_key, old_entry.m_value, old_entry.m_hash_value);
		}
	}
	unsigned int ele_num = m_ele_num;
	clear();
	m_table = std::move(new_table);
	m_ele_num = ele_num;
}

template<typename K, typename V>
std::pair<bool, std::pair<K, V>> hash_table_separatechaining<K, V>::remove(K key)
{
	size_t bucket_index = std::hash<K>()(key) % m_table_size;
	Entry<K, V> temp(key, V{});
	for (auto it = m_table[bucket_index].begin(); it != m_table[bucket_index].end(); it++)
	{
		if (*it == temp)
		{
			V deleted = it->m_value;
			m_table[bucket_index].erase(it);
			m_ele_num--;
			return make_pair(true, make_pair(key, deleted));
		}
	}
	return make_pair(false, make_pair(key, V{}));
}

//想要在查询失败返回V的默认值可以写成V value{}，表示使用列表初始化默认构造V
//如果不确定 V 一定有默认构造，可以用 std::optional<V> 替代
template<typename K, typename V>
pair<bool, V> hash_table_separatechaining<K, V>::query(K key)
{
	size_t bucket_index = std::hash<K>()(key) % m_table_size;
	Entry<K, V> temp(key, V{});
	for (Entry<K, V>& ele : m_table[bucket_index])
	{
		if (ele == temp)
			return make_pair(true, ele.m_value);
	}
	return make_pair(false, V{});
}

template<typename K, typename V>
void hash_table_separatechaining<K, V>::insert(Entry<K, V> new_entry)
{
	size_t bucket_index = std::hash<K>()(new_entry.m_key) % m_table_size;
	for (Entry<K, V>& ele : m_table[bucket_index])
	{
		if (new_entry == ele)
		{
			ele.m_value = new_entry.m_value;
			return;
		}
	}
	m_table[bucket_index].push_back(new_entry);
	m_ele_num++;
	if (m_ele_num > m_threshold)
		resizetable();
}

template<typename K, typename V>
bool hash_table_separatechaining<K, V>::haskey(K key)
{
	Entry<K, V> temp(key, V{});
	size_t bucket_index = std::hash<K>()(key) % m_table_size;
	for (Entry<K, V>& ele : m_table[bucket_index])
	{
		if (ele == temp)
			return true;
	}
	return false;
}

template<typename K, typename V>
void hash_table_separatechaining<K, V>::clear()
{
	for (list<Entry<K, V>>& chain : m_table)
	{
		chain.clear();
	}
	m_ele_num = 0;
}

template<typename K, typename V>
hash_table_separatechaining<K, V>::hash_table_separatechaining(unsigned int table_size, double load_factor)
	: m_ele_num(0), m_load_factor(load_factor), m_table_size(table_size)
{
	m_table.resize(m_table_size);
	m_threshold = m_table_size * m_load_factor;
}

template<typename K, typename V>
hash_table_separatechaining<K, V>::hash_table_separatechaining()
	: m_ele_num(0), m_table_size(DEFAULT_TABLESIZE), m_load_factor(DEFAULT_LOADFACTOR)
{
	m_table.resize(m_table_size);
	m_threshold = (unsigned int)((double)m_table_size * m_load_factor);
}


int main(void)
{
	hash_table_separatechaining<string, unsigned int> student;
	unsigned int operation_num;
	cin >> operation_num;
	unsigned int operation, score;
	string name;
	pair<bool, pair<string, unsigned>> res3;
	pair<bool, unsigned int> res2;
	while (operation_num--)
	{
		cin >> operation;
		//在 switch 语句里，变量的声明会跨越所有case, 但初始化程可能被跳过,加一层大括号
		switch (operation)
		{
		case 1:
		{
			cin >> name >> score;
			Entry<string, unsigned int> data(name, score);
			student.insert(std::move(data));
			cout << "OK" << endl;
			break;
		}
		case 3:
			cin >> name;
			res3 = student.remove(name);
			if (res3.first)
				cout << "Deleted successfully" << endl;
			else
				cout << "Not found" << endl;
			break;
		case 2:
			cin >> name;
			res2 = student.query(name);
			if (res2.first)
				cout << res2.second << endl;
			else
				cout << "Not found" << endl;
			break;
		case 4:
			cout << student.m_ele_num << endl;
		}
	}

}