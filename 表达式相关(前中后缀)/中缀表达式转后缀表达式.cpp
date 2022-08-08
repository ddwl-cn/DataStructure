#include<iostream>
#include<stack>
#include<string>
using namespace std;
string CHAR2STR(char ch) { string temp; return temp + ch; }
// prefix infix suffix
// 中缀转后缀(逆波兰表达式)
string IN2SUF(string infix){
	// 中间栈、结果栈
	stack<string> s1, s2;
	for (int i = 0; i < infix.size(); i++) {
		// 操作数
		// 多位数字需要拼接一下
		if (isdigit(infix[i])) {
			string sub = "";
			while(i < infix.size() && isdigit(infix[i])) {
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
				// 此时s1栈顶是左括号直接入栈
				if (!s1.empty() && s1.top() == "(") {
					s1.push(CHAR2STR(infix[i]));
				}
				else {
					// 如果要压入的是 + 或 - 因为没有运算符优先级比他俩低 所以之前的符号全部从s1中压入s2
					// 除非遇到 ( 或栈为空 否则s1一直出栈
					if (infix[i] == '-' || infix[i] == '+') {
						while (!s1.empty() && s1.top() != "(") {
							s2.push(s1.top());
							s1.pop();
						}
						s1.push(CHAR2STR(infix[i]));
					}
					// 与 + - 类似 只是 * / 有比他俩优先级低的左移可以在遇到 + - 时就停止
					else if (infix[i] == '*' || infix[i] == '/') {
						while (!s1.empty() && s1.top() != "+" && s1.top() != "-" && s1.top() != "(") {
							s2.push(s1.top());
							s1.pop();
						}
						s1.push(CHAR2STR(infix[i]));
					}
				}

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
int main() {
	string s = "(1+2)*((3/5)+1/(45+5)*51-8)";
	cout << IN2SUF(s);
	return 0;
}