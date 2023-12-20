#include <stdio.h>
int Comp; //比较次数
int Move; //移动次数
void select_sort(int arr[], int n) {
Move = 0, Comp = 0;
	for (int i = 0; i < n; ++i) {
		int index = i;
		int min = arr[i];
		for (int j = i; j < n; ++j) {
			if(++Comp && min > arr[j]) {
				min = arr[j];
				index = j;
				++Move;
			}
		}
		arr[index] = arr[i];
		arr[i] = min;
		++Move;
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
	select_sort(arr, 9);
	Print(arr, 9);
}
