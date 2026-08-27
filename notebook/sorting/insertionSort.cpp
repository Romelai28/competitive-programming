void swap(vector<int> &arr, int j, int i){
	int oldValue = arr[i];
	arr[i] = arr[j];
	arr[j] = oldValue;
}

void insertionSort(vector<int> &arr){
	// Worst case: O(n^2) - Reversed order
	// Best case: O(n) - n repetions of an element
	// The algorithm is stable and in place
	int n = SIZE(arr);

	forsn(i, 1, n){
		int j = i;
		while (0 < j && arr[j - 1] > arr[j]){
			swap(arr, j, j - 1);
			j--;
		}
	}
}

