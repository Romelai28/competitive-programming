struct SqrtDescomposition{
	vi A;
	vector<vi> descompositionOfA;
	vi minOfDescomposition;
	int n, sqrtOfN;

	SqrtDescomposition(vi &arr) : A(arr){
		n = SIZE(arr);
		sqrtOfN = (int) sqrt(n) + 1;
		descompositionOfA.resize(sqrtOfN);
		minOfDescomposition.resize(sqrtOfN, INF);

		forn(i, n) descompositionOfA[i/sqrtOfN].pb(A[i]);
	}

	int findBlock(int index){
		return index/sqrtOfN;
	}
	
	int findIndexInTheBlock(int index){
		return index % sqrtOfN;
	}
	
	void answerQuery(int l, int r){
		int blockOfL = findBlock(l), blockOfR = findBlock(r);
		int indexOfL = findIndexInTheBlock(l), indexOfR = findIndexInTheBlock(r);
		
		if (blockOfL == blockOfR){
			forsn(i, indexOfL, indexOfR+1) // Proceso el intervalo del bloque particular
		} else {
			forsn(i, indexOfL, SIZE(descompositionOfA[blockOfL])) // Itero primer bloque
			forn(i, indexOfR+1) // Itero ultimo bloque
			forsn(i, blockOfL+1, blockOfR) // Itero entre los bloques
		}
	}
}