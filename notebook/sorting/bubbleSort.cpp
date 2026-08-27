void swap(vector<int> &arr, int j, int i){
	int oldValue = arr[i];
	arr[i] = arr[j];
	arr[j] = oldValue;
}

void bubbleSort(vector<int> &arr){
	int n = SIZE(arr);

	forn(i, n){
		forsn(j, 1, n-i) {
			if (arr[j - 1] > arr[j]) swap(arr, j - 1, j);
		}
	}
}
