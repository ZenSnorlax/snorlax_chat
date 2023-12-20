#include <stdio.h>
int Comp; //比较次数
int Move; //移动次数
void insert_sort(int arr[], int n) {
	int temp, j, i;
	Comp = 0, Move = 0;
	for (i = 1; i < n; i++) {
		temp = arr[i];
		for (j = i - 1; j >= 0 && temp < arr[j]; j--) {
			arr[j + 1] = arr[j];
		}
		Comp += i - j;
		
		arr[j + 1] = temp;
		Move += i - j;
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
	insert_sort(arr, 9);
	Print(arr, 9);
}
