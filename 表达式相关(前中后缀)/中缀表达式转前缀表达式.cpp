#include<iostream>
#include<stack>
#include<string>
#include<algorithm>
#include<assert.h>
using namespace std;
string CHAR2STR(char ch) { string temp; return temp + ch; }
char STR2CHAR(string s) { return s.c_str()[0]; }
// 获得字符优先级
int getPriority(char c) {
	if (c == '-' || c == '+') return 1;
	if (c == '*' || c == '/') return 2;
	return 0;
}
// 中缀转前缀(波兰表达式)
string IN2PRE(string infix) {
	string res = "";
	stack<string> s1, s2;
	// 中缀转前缀需要从后往前扫描
	for (int i = infix.size() - 1; i >= 0; i--) {
		if (infix[i] == ' ') continue;
		// 如果是数字可以直接加入输出结果中
		if (isdigit(infix[i])) {
			while (i >= 0 && (isdigit(infix[i]) || infix[i] == '.')) {
				res += infix[i--];
			}
			res += " ";
			i++;
		}
		else {
			// 右括号直接入栈
			if (infix[i] == ')') {
				s1.push(CHAR2STR(infix[i]));
			}
			// 左括号则将右括号前的栈中元素全部退出
			else if(infix[i] == '(') {
				while (s1.top() != ")") {
					res += s1.top();
					res += " ";
					s1.pop();
				}
				s1.pop();
			}
			else {
				// 栈顶元素优先级更高就一直出栈
				while (!s1.empty() && getPriority(infix[i]) < getPriority(STR2CHAR(s1.top()))) {
					res += s1.top();
					res += " ";
					s1.pop();
				}
				s1.push(CHAR2STR(infix[i]));
			}

		}
	}
	// s1中剩余符号出栈
	while (!s1.empty()) {
		res += s1.top();
		res += " ";
		s1.pop();
	}
	// 反转过来就是结果
	reverse(res.begin(), res.end());
	return res.substr(1, res.size()-1);
}
double calculatePREFIX(string prefix) {
	stack<double> s;
	for (int i = prefix.size() - 1; i >= 0; i--) {
		if (prefix[i] == ' ') continue;
		if (isdigit(prefix[i])) {
			string t = "";
			while (i >= 0 && (isdigit(prefix[i]) || prefix[i] == '.')) {
				t += prefix[i--];
			}
			i++;
			// 这里需要注意 从后往前得到的数字字符串是反的 需要翻转过来
			reverse(t.begin(), t.end());
			s.push(stod(t));
		}
		else {
			double a = s.top();
			s.pop();
			double b = s.top();
			s.pop();
			if (prefix[i] == '+') {
				s.push(a + b);
			}
			else if (prefix[i] == '-') {
				s.push(a - b);
			}
			else if (prefix[i] == '*') {
				s.push(a * b);
			}
			else {
				s.push(a / b);
			}
		}
	}
	double t = s.top();
	s.pop();
	return t;
}
int main() {
	string s = "(1+2)*((3/5)+1/(45+5)*51-8)";
	string y = "(1+2)*8";

	cout << "前缀表达式为：" << IN2PRE(s) << endl;
	cout << "前缀表达式的值为：" << calculatePREFIX(IN2PRE(s)) << endl;
	return 0;
}