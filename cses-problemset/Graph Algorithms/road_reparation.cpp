#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const ll UNDEFINED = -1;
 
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
#define pb push_back
  
// ############################################################### //

struct DisjointSet{
    vector<ll> parent, rnk;
    
    DisjointSet(ll n){
        rnk.assign(n, 0);
        for (ll i = 0; i < n; i++)
            parent.push_back(i);
    }
 
    ll findSet(ll x){
        if(parent[x]==x) return x;
        parent[x] = findSet(parent[x]);
        return parent[x];
    }
 
    void unionSet(ll x, ll y){
        // Encontrar los representantes del conjunto.
        x = findSet(x);
        y = findSet(y);
 
        // Si los conjuntos son disjuntos:
        if (x != y){
            // Pongo al que tiene menos rango por debajo del de mayor rango.
            if (rnk[x] < rnk[y]){
                parent[x] = y;
            } else if (rnk[x] > rnk[y]){
                parent[y] = x;
            } else {  // Si tienen el mismo rango, incremento del rango.  (rnk[x] == rnk[y])
                parent[y] = x;
                rnk[x]++;
            }
        }
    }
};
 
 
ll kruskal(ll n, vector<pair<ll, pair<ll, ll>>> &lista_edges){
    // Devuelve el costo del AGM. En caso de que no sea conexo, devuelve -1.
    sort(lista_edges.begin(),lista_edges.end());
    DisjointSet dsu(n+1);
    ll res = 0;
    for(auto e : lista_edges){
        ll peso = e.first;
        ll x = (e.second).first;
        ll y = (e.second).second;
 
        if (dsu.findSet(x) != dsu.findSet(y)){
            dsu.unionSet(x, y);
            res += peso;
            n--;  // Para verificar luego si es posible visitar todos.
        }
    }
 
    if(n!=1){res = -1;}  // No era conexo.
    return res;
}
 
 
int main()
{
    // Lectura inputs:
    ll n, m, a, b, c;
    cin >> n >> m;
 
    // Represento al grafo como una lista de aristas.
    vector<pair<ll, pair<ll, ll>>> lista_edges(m);
    for(ll i=0; i<m; i++){
        cin >> a >> b >> c;
        lista_edges.pb({c, {a,b}});
    }
 
    ll res = kruskal(n, lista_edges);
 
    if(res == -1){
        cout << "IMPOSSIBLE";
    } else {
        cout << res;
    }
 
    return 0;
}
