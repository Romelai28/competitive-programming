// D&C version
ll maximumContiguosSumFromMiddle(vl &A){
	ll res = 0;
	int n = SIZE(A), middle = n/2;
	ll currentLeftSum = A[middle], currentRightSum = 0;
	ll maximumLeft = A[middle], maximumRight = 0;

	dforn(j, middle){ 
		currentLeftSum += (ll) A[j];
		maximumLeft = max(maximumLeft, currentLeftSum);
	}

	forsn(j, middle+1, n){
		currentRightSum += (ll) A[j];
		maximumRight = max(maximumRight, currentRightSum);
	}

	res = maximumLeft + max(maximumRight, 0);
	return res;
}

ll maximumSubArraySum(vl &A){
	ll res = 0;
	int n = SIZE(A);

	if (n == 1) return A[0];
	else if (n == 0) return NEG_INF; // Esto es para no permitir array vacio

	int middle = n/2;
	vl left, right;
	forn(i, middle) left.pb(A[i]);
	forsn(i, middle, n) right.pb(A[i]);
	
	ll middleSum = maximumContiguosSumFromMiddle(A), leftSum = maximumSubArraySum(left), rightSum = maximumSubArraySum(right);
	res = max(middleSum, max(leftSum, rightSum));
	return res;
}
