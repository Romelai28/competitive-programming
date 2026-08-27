void swap(vector<int> &arr, int j, int i)
{
	int oldValue = arr[i];
	arr[i] = arr[j];
	arr[j] = oldValue;
}

int partition(vector<int> &arr, int l, int h)
{
	// Note: If the input array is already sorted, the current method of pivot selection may not be optimal. To mitigate this issue, an alternative approach is to select the pivot randomly, either by using a library function or by randomly permuting the array.
	int p = h; // Select pivot as the last element
	int finalPivotPosition = l; // All the elements less than the pivot will be before this index

	forsn(i, l, h){
		if (arr[i] < arr[p]){
			swap(arr, i, finalPivotPosition);
			finalPivotPosition++;
		}
	}

	swap(arr, finalPivotPosition, p); // I update the pivot position to divide the array correctly
	return finalPivotPosition; // I return the correct pivot position
}

void quickSortAlgorithm(vector<int> &arr, int l, int h){
	if (l < h){
		int p = partition(arr, l, h);  // partition puts the pivot in the correct position for the sorted array
		quickSortAlgorithm(arr, l, p - 1); // I call the quickSortAlgorithm to sort the array of elements smaller than the pivot
		quickSortAlgorithm(arr, p + 1, h); // I call the quickSortAlgorithm to sort the array of elements greater than the pivot
	}
}

void quickSort(vector<int> &arr)
{   
	// Worst case: O(n^2)
	// Best case and average case: O(n log n)
	// This algorithm is in place

	int n = arr.size() - 1;
	quickSortAlgorithm(arr, 0, n); // I call the quickSortAlgorithm to sort the array in the range [0, n]
}

