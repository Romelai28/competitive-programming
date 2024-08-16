// La matriz tuvo que ser inicializada como:
// d(s,v) = w(s,v) si existe
// d(s,v) = 0   si s = v
// d(s,v) = INF si no

void floyd_warshall (ll n, vector<vector<ll>> &matrizDist){
    // matrizDist en la entrada era la matriz de distancias diractas, luego del algoritmo queda calculada en ella APSP. (Distancias minimas i->j)
    for (ll k = 0; k < n; ++k) {
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < n; ++j) {
                if (matrizDist[i][k] < LINF && matrizDist[k][j] < LINF){
                    matrizDist[i][j] = min(matrizDist[i][j], matrizDist[i][k] + matrizDist[k][j]);
                }
            }
        }
    }
}
