#include<iostream>
using namespace std;
// 冒泡排序 略
// 插入排序
// 时: O(n)~O(n^2) 空: O(1)
// 稳定！
void InsertSort(int Array[], int s, int e) {
	if (s >= e) return;

	for (int i = s + 1; i <= e; i++) {
		// 记录下当前要插入元素
		int base = Array[i];
		int j = i - 1;
		for (; j >= 0; j--) {
			if (Array[j] > base) {
				Array[j + 1] = Array[j];
			}
			else break;
		}
		// 插入到正确位置
		Array[j + 1] = base;
	}
}
// 折半插入排序 
// 时: O(n)~O(n^2) 空: O(1) 
// 稳定！只是减少了比较次数时间复杂度并没有改变
void BinaryInsertSort(int Array[], int s, int e) {
	if (s >= e) return;

	for (int i = s + 1; i <= e; i++) {
		int base = Array[i];
		int l = 0, r = i - 1, mid;
		while (l < r) {
			mid = (l + r) >> 1;
			if (Array[mid] > base) r = mid - 1;
			// 遇到大小相同的元素 就放到右侧 保证排序稳定性
			else l = mid + 1;
		}
		// 移动
		for (int j = i - 1; j >= r + 1; j--) 
			Array[j + 1] = Array[j];
		// 插入
		Array[r + 1] = base;
	}
}
// 希尔排序
// 时: O(n^1.3~n^2) 空: O(1)
// 不稳定！
void ShellSort(int Array[], int s, int e) {
	if (s == e) return;
	// 确定步长 为数组长度/2
	
	// 每次步长除二
	for (int d = (e - s + 1) >> 1; d >= 1; d /= 2) {
		// 当前元素小标从s+d开始
		// 每次当前元素比较的对象是和它间隔为d的元素
		for (int i = s + d; i <= e; i++) {
			// 如果当前元素顺序不正确就进行插入
			if (Array[i] < Array[i - d]) {
				int base = Array[i];
				int j = i - d;
				for (; j >= 0 && Array[j]>base; j -= d) {
					Array[j + d] = Array[j];
				}
				Array[j + d] = base;
			}
		}
	}
}
// 快速排序(重要)
// 时: O(nlogn)~O(n^2) 空: O(logn)~O(n)
// 不稳定！排序后相同数字间的位置会发生改变
void QuickSort(int Array[], int low, int high) {
	
	if (low >= high) return;
	int l = low, r = high;
	// 提取基准值
	int base = Array[high];
	while (low < high) {
		// 左边都比基准值小
		while (low < high && Array[low] <= base) low++;
		Array[high] = Array[low];
		// 右边都比基准值大
		while (low < high && Array[high] >= base) high--;
		Array[low] = Array[high];
	}
	// 最后放置基准值
	Array[low] = base;
	
	// 一分为二 递归的排序
	QuickSort(Array, l, low - 1);
	QuickSort(Array, low + 1, r);
}
int main() {
	int arr[10] = { 5,3,1,8,4,10,3,5,1,11 };
	ShellSort(arr, 0, 9);
	for (auto it : arr) {
		cout << it << ' ';
	}
	return 0;
}