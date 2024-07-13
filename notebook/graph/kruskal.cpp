// Asume grafo representado como lista de aristas.

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