vector<int> divisoresOf(int a){
	vector<int> res;
	int until = sqrt(a) + 1;
	forsn(i, 1, until){
		if (a % i == 0) res.pb(i);
		if (a % i == 0 && i != a/i) res.pb(a/i);
	}

	return res;
}

int sumDigits(int m) {
	int sum = 0;
	while (m > 0) {
		sum += m % 10;
		m /= 10;      
	}
	return sum;
}

// pow(2, k) = 1 << k, esto es un shift izquierdo