void dantzig(ll n, vector<vector<peso>> &matrizDist){
    // matrizDist en la entrada era la matriz de distancias diractas, luego del algoritmo queda calculada en ella APSP.
    for(ll k=0; k<n; k++){

        for(ll i=0; i<k; i++){
            for(ll j=0; j<k; j++){
                matrizDist[i][k] = min(matrizDist[i][k], matrizDist[i][j] + matrizDist[j][k]);
                matrizDist[k][i] = min(matrizDist[k][i], matrizDist[k][j] + matrizDist[j][i]);
            }
        }

        for(ll i=0; i<k; i++){
            for(ll j=0; j<k; ++j){
                matrizDist[i][j] = min(matrizDist[i][j], matrizDist[i][k] + matrizDist[k][j]);
            }
        }
    }
}