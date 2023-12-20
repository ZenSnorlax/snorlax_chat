#include <stdio.h>
void quick_sort(int arr[], int l, int r) {
	if (l >= r)
		return;
	int pivotkey = arr[l];
	int begin = l;
	int end = r;
	while (l < r) {
		while (l < r && pivotkey <= arr[r])
			--r;
		arr[l] = arr[r];
		arr[r] = pivotkey;
		while (l < r && pivotkey >= arr[l])
			++l;
		arr[r] = arr[l];
		arr[l] = pivotkey;
	}
	quick_sort(arr, begin, l - 1);
	quick_sort(arr, l + 1, end);
}
void Print(int arr[], int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}
int main() {

	int arr[] = {1, 3, 3, 2, 0, 61, 17, 18, 91, 0};
	quick_sort(arr, 0, 9);
	Print(arr, 10);
}
