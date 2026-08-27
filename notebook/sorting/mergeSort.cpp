vi merge(vi &arr1, vi &arr2){
	int n = SIZE(arr1), m = SIZE(arr2), t = n + m;
	vi res(t);
	int j = 0, h = 0;

	forn(i, t){
		if (j < n && h < m){
			if (arr1[j] <= arr2[h]){
				res[i] = arr1[j];
				j++;
			} else {
				res[i] = arr2[h];
				h++;
			}
		} else if (j < n) {
			res[i] = arr1[j];
			j++;
		} else {
			res[i] = arr2[h];
			h++;
		}
	}

	return res;
}

vi mergeSort(vi &arr){   
	// Worst and best case: O(n * log n)
	// The algorithm is stable but not in place
	int n = SIZE(arr);
	if (n <= 1) return arr;

	int mid = n / 2;
	vi leftHalf, rightHalf;

	forn(i, mid) leftHalf.push_back(arr[i]);
	forsn(i, mid, n) rightHalf.push_back(arr[i]);
	
	vi res1 = mergeSort(leftHalf);
	vi res2 = mergeSort(rightHalf);
	return merge(res1, res2);
}
