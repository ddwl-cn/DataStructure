#include<iostream>
#include<list>
using namespace std;
#define MAX_LENGTH 25
// 值得注意的是key的取值一般是最接近数组长度的素数
const int key = 23;
// 链式存储法
list<int> hashList[MAX_LENGTH];
// 顺序表存储
int hashArray[MAX_LENGTH] = {-1, };


// 开放定址法 分为三种方式(主要应用于固定大小的顺序表)
// (1)、线性探测再散列(重要)
// (2)、平方探测再散列
// (3)、随机探测在散列(就是一个随机的序列不怎么重要)
void putHash_1(int value) {
	// 散列步长 每次加一 {1, 2, 3, ..., n}
	int d = 1;
	int hash = value % key;
	if (hashArray[hash] == -1) hashArray[hash] = value;
	else {
		// 直到不再冲突 如果遍历一遍后仍然没有空余说明空间已满
		while (hashArray[(hash + d) % MAX_LENGTH] != -1 && d < MAX_LENGTH) d++;
		if (d >= MAX_LENGTH) exit(-1);

		hashArray[(hash + d) % MAX_LENGTH] = value;
	}
}
void putHash_2(int value) {
	// 散列步长 平方探测 {1, -1, 4, -4, 9, -9, ..., n^2, -n^2}\
	// 需要注意 n<数组长度/2......................................
	int d = 1;
	int hash = value % key;
	if (hashArray[hash] == -1) hashArray[hash] = value;
	else {
		int k = 1;
		// 直到不再冲突 如果遍历一遍后仍然没有空余说明空间已满
		while (hashArray[(hash + k * d * d) % MAX_LENGTH] != -1 && d < MAX_LENGTH / 2) {
			k *= -1;
			if (k == 1) d++;
		}
		if (d >= MAX_LENGTH / 2) exit(-1);

		hashArray[(hash + k * d * d) % MAX_LENGTH] = value;
	}
}

// 链地址法(主要应用于链表)
void putHash_3(int value) {
	int hash = (value % key);
	hashList[hash].push_back(value);
}
// 还有一个再散列法 其实就是准备多个hash函数 冲突后就尝试另一个hash函数
// 另外hash表中是不允许有重复值的 代码中未开考虑这一点 不过应当知道
int main() {
	srand(0);
	for (int i = 0; i < MAX_LENGTH; i++) {
		hashArray[i] = -1;
	}
	for (int i = 1; i <= 10; i++) {
		putHash_3(rand() % 200);
	}
	//for (int i = 0; i < MAX_LENGTH; i++) {
	//	cout << hashArray[i] << ' ';
	//}

	for (int i = 0; i < MAX_LENGTH; i++) {
		cout << "[" << i << "]";
		for (auto it : hashList[i]) {
			cout << " <- " << it;
		}
		putchar(10);
	}
	return 0;
}