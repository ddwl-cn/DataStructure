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
// prefix infix suffix
// 中缀转后缀(逆波兰表达式)
string IN2SUF(string infix){
	// 中间栈、结果栈
	stack<string> s1, s2;
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == ' ') continue;
		// 操作数
		// 多位数字需要拼接一下
		if (isdigit(infix[i])) {
			string sub = "";
			while(i < infix.size() && (isdigit(infix[i]) || infix[i] == '.')) {
				sub += infix[i++];
			}
			i--;
			s2.push(sub);
		}
		// 操作符
		else {
			// 左括号直接入栈
			if (infix[i] == '(') {
				s1.push("(");
			}
			// 遇到右括号就把与之匹配的左括号前的符号全部出栈压入s2中
			else if(infix[i]==')') {
				while (s1.top() != "(") {
					s2.push(s1.top());
					s1.pop();
				}
				s1.pop();
			}
			// 运算符
			else {
					while (!s1.empty() && getPriority(infix[i]) <= getPriority(STR2CHAR(s1.top()))) {
						s2.push(s1.top());
						s1.pop();
					}
					s1.push(CHAR2STR(infix[i]));
			}
		}
	}
	// 将s1中剩余的压入s2
	while (!s1.empty()) {
		s2.push(s1.top());
		s1.pop();
	}

	// s2中顺序出栈后是逆序的 需要翻转一下
	stack<string> res;
	while (!s2.empty()) {
		res.push(s2.top());
		s2.pop();
	}
	string temp = "";
	while (!res.empty()) {
		temp += res.top() + " ";
		res.pop();
	}
	return temp;
}
double calculateSUFFIX(string suffix) {
	stack<double> s;
	for (int i = 0; i < suffix.size(); i++) {
		if (suffix[i] == ' ') continue;
		if (isdigit(suffix[i])) {
			string t = "";
			while (i < suffix.size() && (isdigit(suffix[i]) || suffix[i] == '.')) {
				t += suffix[i++];
			}
			i--;
			s.push(stod(t));
		}
		else {
			double a = s.top();
			s.pop();
			double b = s.top();
			s.pop();
			if (suffix[i] == '+') {
				s.push(a + b);
			}
			else if (suffix[i] == '-') {
				s.push(b - a);
			}
			else if (suffix[i] == '*') {
				s.push(a * b);
			}
			else {
				s.push(b / a);
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

	cout << "后缀表达式为：" << IN2SUF(s) << endl;
	cout << "后缀表达式的值为：" << calculateSUFFIX(IN2SUF(s)) << endl;
	return 0;
}