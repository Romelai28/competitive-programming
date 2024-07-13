#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const ll UNDEFINED = -1;
 
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ll zero = 0;
#define pb push_back
 
using peso = ll;
using indice_nodo = ll;
using nodo_pesado = pair<peso, indice_nodo>;

struct Edge {
    ll a, b, cost;

    Edge(ll desde, ll hasta, ll c) : a(desde), b(hasta), cost(c) {}
};
 
// ############################################################### //
 
void dfs(ll v, vector<unordered_set<ll>> &ady, vector<bool> &vis){
    vis[v] = true;
    for(ll u : ady[v]){
        if (vis[u] != true){
            dfs(u, ady, vis);
        }
    }
}
 
 
bool bellman_ford(ll n, indice_nodo inicio, vector<Edge> &edges, vector<peso> &dist){
    // Devuelve true sii existe un ciclo de longitud negativa.
    // Calcula SSSP en dist.
 
    // Obtiene las distancias más cortas desde inicio hacia todos.
    dist[inicio] = 0;
    for(ll i=0; i<n; i++){
        for(Edge e : edges){
            if(-LINF < dist[e.a] && dist[e.a] < LINF){
                dist[e.b] = min(dist[e.b], dist[e.a] + e.cost);
            }
        }
    }
 
    // Detectar ciclo de longitud negativa.
    for(Edge e : edges){
        if(-LINF < dist[e.a] && dist[e.a] < LINF){
            if (dist[e.a] + e.cost < dist[e.b]){
                return true;
            }
        }
    }
    return false;
}



int main()
{
    // En el problema se asume que se puede viajar desde 1 hasta n.
    // Leer inputs:
    ll n, m, a, b, c;
 
    cin >> n >> m;
 
    // Representamos al grafo -G como una lista de aristas.
    vector<Edge> edgesInv;  // -G: En edges inv todos los costos fueron multiplicados por -1.
 
    // Representamos al grafo G transpuesto como una lista de adyacencia.
    vector<unordered_set<ll>> adyGT(n+1);
    vector<bool> vis(n+1, false);
 
    for(ll i=0; i<m; i++){
        cin >> a >> b >> c;
        edgesInv.pb(Edge(a, b, -c));
        adyGT[b].insert(a);
    }
 
    // Resuelvo y output:
    vector<peso> dist(n+1, LINF);
    dist[1] = 0;
 
    // Detecto los nodos que no son alcanzables desde n en GT.
    dfs(n, adyGT, vis);
 
    // Limpio -G eliminandolos.
    vector<Edge> edgesInvLimpio;
    for(Edge e : edgesInv){
        if (vis[e.a] && vis[e.b]){
            edgesInvLimpio.pb(e);
        }
    }
 
    if (bellman_ford(n, 1, edgesInvLimpio, dist)){
        // Hay un ciclo de long. negativa en -G:
        cout << -1;
    } else {
        // NO hay un ciclo de long. negativa:
        cout << -dist[n];
    }
 
    return 0;
}
