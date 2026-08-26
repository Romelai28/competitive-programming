struct BinaryJumping{
	vvi jump; int n, logk;
	// Inicializacion O(nlog(MAX_K))
	BinaryJumping(vi &succ, int max_k) : n(SIZE(succ)) {
		logk = (int) log2(max_k);
		jump.assign(n, vi(logk+1, UNDEFINED));
		forn(i, n) {jump[i][0] = succ[i];}
		forsn(it, 1, logk+1){
			forn(i, n) {
				if (jump[i][it-1] != UNDEFINED) jump[i][it] = jump[jump[i][it-1]][it-1];
			}
		}
	}
	// Query O(log(k)). Donde x es el nodo, k es la distancia de salto.
	int succ_k(int x, int k){
		assert(k >= 0);
		for(int it = 0; k > 0; it++, k >>= 1){
			if(k & 1 && x != UNDEFINED) x = jump[x][it];
		}
		return x; // x = UNDEFINED significa que te excediste con los saltos
	}
};
