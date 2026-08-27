void dantzig(ll n, vector<vector<peso>> &matrizDist){
	// matrizDist en la entrada era la matriz de distancias diractas, luego del algoritmo queda calculada en ella APSP.
	forn(k, n){
		forn(i, k) forn(j, k){
			matrizDist[i][k] = min(matrizDist[i][k], matrizDist[i][j] + matrizDist[j][k]);
			matrizDist[k][i] = min(matrizDist[k][i], matrizDist[k][j] + matrizDist[j][i]);
		}

		forn(i, k) forn(j, k) matrizDist[i][j] = min(matrizDist[i][j], matrizDist[i][k] + matrizDist[k][j]);
	}
}