void countingSort(vector<int> &arr, int n){
	// We know that: n <= arr.length, the array doesn't have negative elements and every element in the array is <= n
	// Best and worst case: O(n)
	// The algorithm is in place

	int m = SIZE(arr);
	vector<int> repetitions(n + 1, 0);

	forn(i, m){
		int index = arr[i];
		repetitions[index]++;
	}

	int j = 0;

	forn(i, n+1){
		forn(k, repetitions[i]){
			arr[j] = i;
			j++;
		}
	}
}
