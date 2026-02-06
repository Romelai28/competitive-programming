// Quiero saber el valor de f(j, i) donde f(j, i) = min(f(j-1, c) + cost(c+1, i)) para algun c < i
// Para poder optimizarlo tengo que cumplir la propiedad de que el c que minimiza f(j, i) es <= al c' que minimiza f(j, i+1)

ll costs(int i, int j){
    // Asume i <= j, y calcula el costo del subarray [A[i], ..., A[j]]
    // TO DO
}

void optimization(int k, int l, int r, int optL, int optR, vector<vl> &memo){
    if (l > r) return ;
    int middle = (l + r)/2, optIndex = UNDEFINED;
		
	forsn(c, max(1, optL), min(optR, middle)+1){
		ll value = memo[k-1][c-1] + costs(c, middle);
		if (value < memo[k][middle]) optIndex = c;
		memo[k][middle] = min(memo[k][middle], value);
	}
		
	divide_and_conquer(k, l, middle-1, optL, optIndex, memo);
	divide_and_conquer(k, middle+1, r, optIndex, optR, memo);
}

vector<vl> memo(k+1, vector<vl>(n, LINF));
forn(i, n) memo[1][i] = costs(0, i);
forsn(i, 2, k+1) optimization(i, 0, n-1, 0, n-1, memo);

// La respuesta es memo[k][n-1]