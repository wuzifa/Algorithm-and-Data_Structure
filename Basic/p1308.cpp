#ifdef RUN_P1308
#include <iostream>
#include <string>
using namespace std;

int main() {
	string standard, line;
	getline(cin, standard);
	getline(cin, line);

	// 大小写统一
	for (char& c : standard) c = toupper(c);

	int count = 0;
	int firstPos = -1;

	size_t i = 0;
	while (i < line.size()) {
		// 跳过空格
		while (i < line.size() && line[i] == ' ') i++;
		if (i >= line.size()) break;

		size_t start = i;
		string word;
		while (i < line.size() && line[i] != ' ') {
			word += toupper(line[i]);
			i++;
		}

		if (word == standard) {
			count++;
			if (firstPos == -1) firstPos = start;
		}
	}

	if (count == 0)
		cout << -1 << '\n';
	else
		cout << count << ' ' << firstPos << '\n';

	return 0;
}

#endif 
