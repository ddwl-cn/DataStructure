#include<iostream>
using namespace std;

// 二分查找
int binary_search(int arr[], int s, int e, int value) {
	// 查找的左右边界
	int l = s, r = e;
	while (l < r) {
		// 当然也可以额外判断：如果mid恰好是要找的数就直接退出
		int mid = (l + r) >> 1;
		if (arr[mid] >= value) {
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}
	if (arr[l] != value) l = -1;
	return l;
}
int main() {
	int arr[10] = { 1,3,9,12,55,60,80,100,102, 150 };
	cout << "要查找的数字数组中的下标为：" << binary_search(arr, 0, 9, 12);

	return 0;
}