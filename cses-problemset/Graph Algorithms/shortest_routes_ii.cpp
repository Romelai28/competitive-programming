#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const ll UNDEFINED = -1;
 
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
#define pb push_back

using peso = ll;
using indice_nodo = ll;
using nodo_pesado = pair<peso, indice_nodo>;

// ############################################################### //
 
void floyd_warshall (ll n, vector<vector<peso>> &matrizDist){
    // Almacena en matrizDist la matriz de distancias minimas i->j.
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
 
 
int main()
{
    // Leer inputs:
    ll n, m, q, a, b, costo;
 
    cin >> n >> m >> q;
 
    vector<vector<peso>> dist(n+1, vector<ll>(n+1, LINF));
 
    for(ll i=0; i<=n; i++){
        dist[i][i] = 0;
    }
 
    for(ll i=0; i<m; i++){
        cin >> a >> b >> costo;
        dist[a][b] = min(dist[a][b], costo);
        dist[b][a] = min(dist[b][a], costo);
    }
 
    // Resuelvo:
    floyd_warshall(n+1, dist);
 
    // Respondo las queries:
    for(ll i=0; i<q; i++){
        cin >> a >> b;
        if(dist[a][b] >= LINF){
            cout << -1 << "\n";
        } else {
            cout << dist[a][b] << "\n";
        }
 
    }
 
 
    return 0;
}