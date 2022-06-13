#include<iostream>
// 引用c++ STL库中的栈
#include<stack>
#include<string>
using namespace std;
// (1)、使用栈实现算数表达式转换(前缀表达式也叫波兰表达式、后缀表达式也叫逆波兰表达式)
// (2)、计算表达式的值
// 1+2*(3+4/2)*2
int OpValue(char op) {
	if (op == '+' || op == '-') return 1;
	else if (op == '*' || op == '/') return 2;
	else return 0;
}
// 其实中缀转前缀、后缀可以使用 "加括号法" 手算的时候较为简便
// 一下实现方法如果出现两位及以上数字就不能正常运行了 需要对数字进行特殊处理
string transformToPolish(string eq) {
	stack<char> res, op;
	// 转前缀需要从后向前扫描
	for (int i = eq.length() - 1; i >= 0; i--) {
		// 如果是数字就压入数字栈
		if (isdigit(eq[i])) {
			res.push(eq[i]);
		}
		else if (eq[i] == '+' || eq[i] == '-' || eq[i] == '*' || eq[i] == '/') {
			// 栈空或栈顶是 ')'
			if (op.empty() || op.top()==')') {
				op.push(eq[i]);
			}
			// 当前运算符优先级大于等于栈顶运算符优先级
			else if (OpValue(eq[i]) >= OpValue(op.top())) {
				op.push(eq[i]);
			}
			else {
				// 如果优先级比栈顶元素低就一直吧操作符栈顶元素弹出压入res(结果栈)中
				while (!op.empty() && OpValue(eq[i]) < OpValue(op.top())) {
					res.push(op.top());
					op.pop();
				}
				op.push(eq[i]);
			}
		}
		else if(eq[i] == ')') {
			op.push(eq[i]);
		}
		else {
			// 遇到左括号就将有括号前的所有操作符弹出压入res中
			while (op.top() != ')') {
				res.push(op.top());
				op.pop();
			}
			op.pop();
		}
	}
	// 剩余操作符弹出压入res中
	while (!op.empty()) {
		res.push(op.top());
		op.pop();
	}
	string preEq = "";
	// res按顺序弹出就是前缀表达式
	while (!res.empty()) {
		preEq += res.top();
		preEq += ' ';
		res.pop();
	}
	return preEq;
}
string transformToRePolish(string eq) {
	stack<char> res, op;
	// 转前缀需要从后向前扫描
	for (int i = 0; i < eq.length(); i++) {
		// 如果是数字就压入数字栈
		if (isdigit(eq[i])) {
			res.push(eq[i]);
		}
		else if (eq[i] == '+' || eq[i] == '-' || eq[i] == '*' || eq[i] == '/') {
			// 栈空或栈顶是 ')'
			if (op.empty() || op.top() == '(') {
				op.push(eq[i]);
			}
			// 当前运算符优先级大于等于栈顶运算符优先级
			else if (OpValue(eq[i]) >= OpValue(op.top())) {
				op.push(eq[i]);
			}
			else {
				// 如果优先级比栈顶元素低就一直吧操作符栈顶元素弹出压入res(结果栈)中
				while (!op.empty() && OpValue(eq[i]) < OpValue(op.top())) {
					res.push(op.top());
					op.pop();
				}
				op.push(eq[i]);
			}
		}
		else if (eq[i] == '(') {
			op.push(eq[i]);
		}
		else {
			// 遇到左括号就将有括号前的所有操作符弹出压入res中
			while (op.top() != '(') {
				res.push(op.top());
				op.pop();
			}
			op.pop();
		}
	}
	// 剩余操作符弹出压入res中
	while (!op.empty()) {
		res.push(op.top());
		op.pop();
	}
	string preEq = "";
	// res按顺序弹出就是前缀表达式
	while (!res.empty()) {
		preEq += ' ';
		preEq += res.top();
		res.pop();
	}
	reverse(preEq.begin(), preEq.end());
	return preEq;
}
int getPolishValue(string eq) {
	int res = 0;
	stack<int> num;
	for (int i = eq.length() - 1; i >= 0; i--) {
		if (eq[i] == ' ') continue;
		if (isdigit(eq[i])) {
			num.push(eq[i] - '0');
		}
		else {
			int a = num.top();
			num.pop();
			int b = num.top();
			num.pop();
			if (eq[i] == '+')
				num.push(a + b);
			else if (eq[i] == '-')
				num.push(a - b);
			else if (eq[i] == '*')
				num.push(a * b);
			else
				num.push(a / b);
		}
	}
	res = num.top();
	num.pop();
	return res;
}
int getRePolishValue(string eq) {
	int res = 0;
	stack<int> num;
	for (int i = 0; i < eq.length(); i++) {
		if (eq[i] == ' ') continue;
		if (isdigit(eq[i])) {
			num.push(eq[i] - '0');
		}
		else {
			int a = num.top();
			num.pop();
			int b = num.top();
			num.pop();
			if (eq[i] == '+')
				num.push(a + b);
			else if (eq[i] == '-')
				num.push(b - a);
			else if (eq[i] == '*')
				num.push(a * b);
			else
				num.push(b / a);
		}
	}
	res = num.top();
	num.pop();
	return res;
}
int main() {
	string eq = "1-2*(3-4/2)*2";
	cout <<"波兰表达式：" << transformToPolish(eq) << endl;
	cout << eq << " = " << getPolishValue(transformToPolish(eq)) << endl;
	cout <<"逆波兰表达式：" << transformToRePolish(eq) << endl;
	cout << eq << " = " << getRePolishValue(transformToRePolish(eq)) << endl;

	return 0;
}