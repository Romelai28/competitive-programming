// La matriz tuvo que ser inicializada como:
// d(s,v) = w(s,v) si existe
// d(s,v) = 0   si s = v
// d(s,v) = LINF si no

void floyd_warshall (ll n, vector<vl> &matrizDist){
	// matrizDist en la entrada era la matriz de distancias diractas, luego del algoritmo queda calculada en ella APSP. (Distancias minimas i->j)
	forn(k, n) forn(i, n) forn(j, n) if (matrizDist[i][k] < LINF && matrizDist[k][j] < LINF) 
		matrizDist[i][j] = min(matrizDist[i][j], matrizDist[i][k] + matrizDist[k][j]);
}
