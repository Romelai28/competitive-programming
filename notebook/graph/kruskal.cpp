// Asume grafo representado como lista de aristas.
// Las aristas son (costo, {v, u}) y calculo el min tree
ll kruskal(ll n, vector<pair<ll, pair<ll, ll>>> &lista_edges){
	// Devuelve el costo del AGM. En caso de que no sea conexo, devuelve -1.
	sort(all(lista_edges));
	DisjointSet dsu(n+1);
	ll res = 0;
	for(auto e : lista_edges){
		ll peso = e.first, x = (e.second).first, y = (e.second).second;
		if (dsu.findSet(x) != dsu.findSet(y)){
			dsu.unionSet(x, y);
			res += peso;
			n--;  // Para verificar luego si es posible visitar todos.
		}
	}
 
	if(n != 1) res = -1;  // No era conexo.
	return res;
}