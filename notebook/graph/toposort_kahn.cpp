// Devuelve true sii existe un ciclo en G.
// Si no existe ciclo, en orden queda almacenado un orden topologico de G.
bool toposort(vvi &ady, vi &orden){
	orden.clear();
	vi in_deg(SIZE(ady), 0);
	forn(v, SIZE(ady)) for(const auto u : ady[v]) in_deg[u]++;
	
	queue<int> q; // Si usamos min priority_queue podemos obtener el orden lexicografico mas chico
	forn(v, SIZE(ady)){ if(in_deg[v] == 0) q.push(v);}
	
	while(!q.empty()){
		int v = q.front(); q.pop();
		orden.pb(v);
		for(auto u : ady[v]){
			in_deg[u]--;
			if(in_deg[u] == 0) q.push(u);
		}
	}
	
	return SIZE(orden) != SIZE(ady);  // Retorna true sii hay un ciclo.
}
