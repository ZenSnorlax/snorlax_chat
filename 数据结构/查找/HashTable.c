#define m 20
#define MaxInt 32767
#define H(key) key % 20
#define NULLKEY MaxInt
typedef int KeyType;
typedef struct HahTable {
	KeyType key;
} HashTable[m];
int SearchHash(HashTable HT, KeyType key) {
	int H0 = H(key);
	if (HT[H0].key == NULLKEY)
		return -1;
	else if (HT[H0].key == key)
		return H0;
	else {
		for (int i = 1; i < m; ++i) {
			int Hi = (H0 + i) % m;
			if (HT[Hi].key == NULLKEY)
				return -1;
			else if (HT[i].key == key)
				return Hi;
		}
		return -1;
	}
}
