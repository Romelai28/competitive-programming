
// Devuelve true si encuentra un ciclo.
bool tdfs(ll v, const vector<vl> &ady, vector<Estado> &visited, vl &orden){
	visited[v] = VISITANDO;
	for(auto u : ady[v]){
		if(visited[u] == VISITANDO) return true;
		else if (visited[u] == NO_VISITADO) if(tdfs(u, ady, visited, orden)) return true; 
	}

	orden.pb(v);
	visited[v] = VISITADO;
	return false;
}

// Devuelve true sii existe un ciclo en G.
// Si no existe ciclo, en orden queda almacenado un orden topologico de G.
bool toposort(vector<vl> &ady, vl &orden){
	vector<Estado> visited(SIZE(ady), NO_VISITADO);
	orden.clear();

	forn(v, SIZE(ady)) if (color[v] == NO_VISITADO && tdfs(v, ady, visited, orden)) return true;
	reverse(all(orden));
	return false;
}
