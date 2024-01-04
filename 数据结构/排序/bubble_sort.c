#include <stdio.h>
int Move; // 移动次数
int Comp; // 比较次数
void bubble_sort(int arr[], int n)
{
	int flag = 1;
	int m = n - 1;
	while ((m > 0) && (flag == 1)) {
		flag = 0;
		for (int j = 0; j <= m; j++)
			if (++Comp && arr[j] > arr[j + 1] ) {
				int temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
				Move += 2;
				flag = 1;
				--m;
			}
	}
}
void Print(int arr[], int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
	printf("移动%d次\n", Move);
	printf("比较%d次\n", Comp);
}
int main(int argc, char *argv[]) {
	int arr[] = {1, 3, 3, 2, 0, 61, 17, 18, 91, 0};
	bubble_sort(arr, 9);
	Print(arr, 9);
}
