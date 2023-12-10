int Search_Bin(const char key, int Table[], int len){
	int low = 0 ;
	int high = len - 1;
	while (low <= high) {
		int mid = (low + high)/2;
		if (key == Table[mid]) return mid;
		else if (key < Table[mid]) high = mid - 1;
		else low = mid + 1;
	}
	return -1;
}


