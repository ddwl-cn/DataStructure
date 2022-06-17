#include<iostream>
#include<algorithm>
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
		for (; j >= s; j--) {
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
// 时: O(n^1.3)~O(n^2) 空: O(1)
// 不稳定！
void ShellSort(int Array[], int s, int e) {
	if (s >= e) return;
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
				for (; j >= s && Array[j]>base; j -= d) {
					Array[j + d] = Array[j];
				}
				Array[j + d] = base;
			}
		}
	}
}
// 简单选择排序
// 时: O(n)~O(n^2) 空: O(1)
// 不稳定！
void SelectSort(int Array[], int s, int e) {
	if (s >= e) return;
	for (int i = s; i < e; i++) {
		int index = i;
		for (int j = i; j <= e; j++)
			if (Array[index] > Array[j])
				index = j;
		swap(Array[i], Array[index]);
	}
}
// 堆排序(小根堆)
// 时: O(nlogn) 空: O(1)
// 插入操作 (使用数组模拟堆)
// 注意: 大根堆最后得到的序列为升序，小根堆最后得到的序列为降序！
void Adjust_Max_Heap(int Array[], int s, int e) {
	int parent = s;
	int child = (s << 1) + 1;
	
	while (child <= e) {
		if (child + 1 <= e && Array[child] < Array[child + 1]) child++;
		if (Array[parent] > Array[child]) return;

		swap(Array[parent], Array[child]);
		// 交换完成后下层子堆可能遭到破坏 需要向下继续调整
		parent = child;
		child = (parent << 1) + 1;
	}
}
void HeapSort(int Array[], int s, int e) {
	int size = e - s + 1;
	// 下标从0开始
	// 从最后一个非叶子结点开始遍历 挨个调整堆为大根堆
	for (int i = size / 2 - 1; i >= s; i--) {
		Adjust_Max_Heap(Array, i, e);
	}
	// 此时已经成为一个大根堆但是由于堆的结构顺序遍历其实并不是有序的
	// 我们利用堆的第一个元素一定是最小(最大)的特点，不断将顶部元素与末尾元素交换 就可以保证降序(升序)
	for (int i = e; i > s; i--) {
		swap(Array[i], Array[s]);
		Adjust_Max_Heap(Array, s, i - 1);
	}
}
// 归并排序(一般为二路归并)
// 时: O(nlogn) 空: O(n)
// 合并这个其实就和先前两个链表合并类似
// 稳定！
void Merge(int Array[], int l, int mid, int r) {
	int i, j, k;
	// 辅助数组
	int* tempArray = new int[r - l + 1];
	for (i = l; i <= r; i++)
		tempArray[i - l] = Array[i];
	// i,j 分别指向原数组对应的 l 和 mid + 1 的位置
	// i = 0, j 应该是在 mid - l + 1 的位置
	for (i = 0, j = mid - l + 1, k = l; i <= mid - l && j <= r - l; k++) {
		if (tempArray[i] <= tempArray[j])
			Array[k] = tempArray[i++];
		else
			Array[k] = tempArray[j++];
	}
	while (i <= mid - l) Array[k++] = tempArray[i++];
	while (j <= r - l) Array[k++] = tempArray[j++];
	delete []tempArray;
}
void MergeSort(int Array[], int s, int e) {
	if (s >= e) return;

	int mid = (s + e) >> 1;
	MergeSort(Array, s, mid);
	MergeSort(Array, mid + 1, e);
	Merge(Array, s, mid, e);
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
	//int arr[3] = { 5,1, 3};
	MergeSort(arr, 0, 9);
	for (auto it : arr) {
		cout << it << ' ';
	}
	return 0;
}