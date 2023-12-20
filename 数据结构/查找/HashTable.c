#include <stdio.h>
#include <strings.h>
#define m 16
#define MaxInt 32767
#define H(key) key % 13
#define NULLKEY MaxInt
typedef struct HahTable {
	int key;
} HashTable[m];
// 全局变量 平均时间长度
int len_time;

void init(HashTable HT) {
	for (int i = 0; i < m; ++i)
		HT[i].key = NULLKEY;
}

void CreateHash(HashTable HT, int n) {
	int key;
	for (int i = 0; i < n; i++) {
		scanf("%d", &key);
		int mod = H(key);
		if (HT[mod].key == NULLKEY)
		{
			len_time++;

			HT[mod].key = key;
		}
		else {
			for (int j = 1; j < m; ++j) {
				int mod1 = (mod + j) % 13;

				len_time++;

				if (HT[mod1].key == NULLKEY) {
					
					HT[mod1].key = key;
					break;
				}
			}
		}
	}
}

int SearchHash(HashTable HT, int key) {
	int H0 = H(key);
	if (HT[H0].key == NULLKEY)
		return -1;
	else if (HT[H0].key == key)
		return H0;
	else {
		for (int i = 1; i < m; ++i) {
			int Hi = (H0 + i) % 13;
			if (HT[Hi].key == NULLKEY)
				return -1;
			else if (HT[Hi].key == key)
				return Hi;
		}
		return -1;
	}
}
int main() {
	HashTable HT;
	init(HT);
	int n = 12;
	len_time = 0;
	CreateHash(HT, n);
	printf("散列内容: ");
	for (int i = 0; i < m; i++)
		printf("%d ", HT[i].key);
	printf("\n");
	double LenTime = (double)len_time / n;
	printf("平均查找长度 %.2lf\n", LenTime);
	printf("输入查找数据: ");
	int key;
	scanf("%d", &key);
	int index = SearchHash(HT, key);
	if(index != -1)
		printf("查找成功! 下标%d", index);
	else printf("查找失败!");

	return 0;
}
