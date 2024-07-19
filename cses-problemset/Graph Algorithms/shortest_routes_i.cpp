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
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.
#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl
#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)
#define all(c) (c).begin(),(c).end()

template <typename T>
ostream & operator <<(ostream &os, const vector<T>&v) {
    os << "[";
    forn(i, v.size()) {
        if (i > 0) os << ",";
        os << v[i];
    }
    return os << "]";
}

// ############################################################### //

using peso = ll;
using indice_nodo = ll;
using nodo_pesado = pair<peso, indice_nodo>;


// Devuelve el vector de distancias desde inicio al i-esimo vértice.
vector<ll> dijkstra(const indice_nodo inicio, const vector<vector<nodo_pesado>> &ady){
    vector<ll> distancia(ady.size(), LINF);
    vector<bool> vis(ady.size(), false);

    distancia[inicio] = 0;
    set<nodo_pesado> q;

    q.insert({0, inicio});

    while(!q.empty()){
        ll v = q.begin() -> second;
        q.erase(q.begin());

        if (vis[v]) {continue;}
        vis[v] = true;
        for(const auto& [longitud, u] : ady[v]){
            // Longitud del camino de v hacia u.
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

    vector<vector<nodo_pesado>> ady(n);

    // Representación del grafo como lista de adyacencia.
    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        ady[a].pb({c, b});
    }

    // Resuelvo:
    vector<ll> distancia = dijkstra(0, ady);

    // Output:
    for(ll i=0; i<n; i++){
        cout << distancia[i] << " ";
    }

    return 0;
}
