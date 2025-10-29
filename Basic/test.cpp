#ifdef RUN_TEST
//#include <iostream>
//#include <vector>
//#include <algorithm>
//using namespace std;
//int main(void)
//{
//	int a, b;
//	cin >> a >> b;
//	vector<int> v1, v2, target;
//	v1.resize(a);
//	v2.resize(b);
//	int target_size = min(a, b);
//	target.resize(target_size);
//	for (int i = 0; i < a; i++)
//	{
//		cin >> v1[i];
//	}
//	for (int i = 0; i < b; i++)
//	{
//		cin >> v2[i];
//	}
//	sort(v1.begin(), v1.end(), less<int>());
//	sort(v2.begin(), v2.end(), less<int>());
//	vector<int>::iterator target_end = set_intersection(v2.begin(), v2.end(), v1.begin(), v1.end(), target.begin());
//	for (auto it = target.begin(); it != target_end; it++)
//	{
//		cout << *it << ' ';
//	}
//}

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

// 素数判断函数
bool isPrime(int num) {
	if (num < 2) return false;
	if (num == 2) return true;
	if (num % 2 == 0) return false;
	for (int i = 3; i <= sqrt(num); i += 2) {
		if (num % i == 0) return false;
	}
	return true;
}

// 判断输入是否为纯整数（不包含小数点或其他非数字字符）
bool isInteger(const string& s) {
	// 空字符串无效
	if (s.empty()) return false;
	// 处理正负号
	int start = 0;
	if (s[0] == '+' || s[0] == '-') {
		start = 1;
		// 只有符号的情况（如 "+"、"-"）无效
		if (start >= s.size()) return false;
	}
	// 检查剩余字符是否全为数字
	for (int i = start; i < s.size(); ++i) {
		if (!isdigit(s[i])) {
			return false;
		}
	}
	return true;
}

int main() {
	string input;
	// 读取整行输入（避免因空格分割导致的问题）
	getline(cin, input);

	// 检查输入是否为纯整数
	if (!isInteger(input)) {
		cout << "输入错误" << endl;
		return 0;
	}

	// 转换为整数
	int num;
	istringstream iss(input);
	iss >> num;

	// 判断素数并输出
	if (isPrime(num)) {
		cout << "是素数" << endl;
	}
	else {
		cout << "不是素数" << endl;
	}

	return 0;
}
#endif