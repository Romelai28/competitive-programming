void swap(vector<int> &arr, int j, int i){
	int oldValue = arr[i];
	arr[i] = arr[j];
	arr[j] = oldValue;
}

int minValue(vector<int> &arr, int j){  // The functions return the index of the minimum value
	int n = SIZE(arr); // n > 0
	int min = j;

	forsn(i, j+1, n){
		if (arr[i] < arr[min]) min = i;
	}

	return min;
}

void selectionSort(vector<int> &arr){
	// Worst and best case: O(n^2)
	// The algorithm is stable and in place

	int n = SIZE(arr);

	forn(i, n){
		int min = minValue(arr, i);
		swap(arr, min, i);
	}
}
