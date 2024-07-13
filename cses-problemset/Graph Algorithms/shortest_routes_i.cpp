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

vector<ll> dijkstra(ll n, indice_nodo inicio, vector<vector<nodo_pesado>> &ady){
    // Devuelve el vector de distancias desde inicio al i-esimo vértice.

    vector<ll> distancia(n+1, LINF);
    vector<bool> vis(n+1, false);
 
    distancia[inicio] = 0;
    set<nodo_pesado> q;
 
    q.insert({0, inicio});
 
    while(!q.empty()){
        ll v = q.begin() -> second;
        q.erase(q.begin());
 
        if (vis[v]) {continue;}
        vis[v] = true;
        for(auto edge : ady[v]){
            ll u = edge.second;
            ll longitud = edge.first;  // Longitud del camino de v hacia u.
            // Relax:
            if(distancia[v] + longitud < distancia[u]){
                q.erase({distancia[u], u});
                distancia[u] = distancia[v] + longitud;
                q.insert({distancia[u], u});
            }
        }
    }
    return distancia;
}
 
 
int main()
{
    // Leer inputs:
    ll n, m;
    cin >> n >> m;
 
    vector<vector<nodo_pesado>> ady(n+1);
 
    // Representación del grafo como lista de adyacencia.
    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        ady[a].pb({c, b});
    }
 
    // Resuelvo:
    vector<ll> distancia = dijkstra(n, 1, ady);
 
    // Output:
    for(ll i=1; i<=n; i++){
        cout << distancia[i] << " ";
    }
 
    return 0;
}
