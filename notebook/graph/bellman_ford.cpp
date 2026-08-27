struct Edge {
	ll a, b, cost;
	Edge(ll desde, ll hasta, ll c) : a(desde), b(hasta), cost(c) {}
};

// Comentario importante: si queremos saber la distancia de inicio a un vertice particular llamado destino tenemos que haber modificado al grafo G original.
// Hay que correr un DFS desde G^T empezando desde destino para poder detectar todos los vertices que son alcanzables desde este y solo agregar las aristas de dichos vertices a nuestro edges
// Esto es para ignorar los ciclos negativos que no pertenecen a ningun recorrido desde inicio a destino

// Asume grafo representado como lista de aristas.

bool bellman_ford(ll n, indice_nodo inicio, vector<Edge> &edges, vl &dist){
	// Devuelve true sii existe un ciclo de longitud negativa.
	// Calcula SSSP en dist.
 
	// Obtiene las distancias mas cortas desde inicio hacia todos.
	dist[inicio] = 0;
	forn(i, n){
		for(Edge e : edges){
			if(-LINF < dist[e.a] && dist[e.a] < LINF) dist[e.b] = min(dist[e.b], dist[e.a] + e.cost);
		}
	}
 
	// Detectar ciclo de longitud negativa.
	for(Edge e : edges){
		if(-LINF < dist[e.a] && dist[e.a] < LINF){
			if (dist[e.a] + e.cost < dist[e.b]) return true;
		}
	}
	return false;
}
