#ifdef RUN_P1449
#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;


int Perform(int op1, int op2, const string& symbol)
{
	if (symbol == "+")
		return op1 + op2;
	if (symbol == "-")
		return op1 - op2;
	if (symbol == "*")
		return op1 * op2;
	
	return op1 / op2;
}



int main(void)
{
	string expr, str;
	cin >> expr;
	vector<string> token;
	for (int i = 0; expr[i] != '@'; i++)
	{
		if (expr[i] == '+' || expr[i] == '*' || expr[i] == '-' || expr[i] == '/')
		{
			str.push_back(expr[i]);
			token.push_back(str);
			str.clear();
		}
		else
		{
			if (expr[i] == '.')
			{
				token.push_back(str);
				str.clear();
			}
			else
			{
				str.push_back(expr[i]);
				if (expr[i + 1] == '@')
					token.push_back(str);
			}
		}
	}
	stack<int> operand;
	int op1, op2;
	for (vector<string>::const_iterator it = token.begin(); it != token.end(); it++)
	{
		if (*it != "+" && *it != "-" && *it != "*" && *it != "/")
			operand.push(stoi(*it));
		else
		{
			op2 = operand.top();
			operand.pop();
			op1 = operand.top();
			operand.pop();
			operand.push(Perform(op1, op2, *it));
		}
	}
	cout << operand.top();
}
#endif