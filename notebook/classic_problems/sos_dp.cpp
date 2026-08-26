// Complexity: O(N * 2^N)
// F[mask] = sum A[i] for all i subset of mask.

// Requiere: F <- A
forn(i, N) {
	forn(mask, 1<<N ){
		if(mask & (1<<i)) {  // Subconjuntos != 0, superconjuntos == 0.
			F[mask] += F[mask^(1<<i)];  // -= para la inversa.
		}
	}
}
