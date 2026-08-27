// Los ciclos siempre se reconstruyen haciendo cycle_end -> parent[cycle_end] -> ... -> cycle_start
// Encontrar ciclo en un grafo no dirigido
bool findCycle(int v, int p){
	visited[v] = true;
	parent[v] = p;

	for (int u : adjList[v]){
		if (u == p) continue; 
		if (visited[u]) {
			cycle_end = v;
			cycle_start = u;
			return true;
		}
		
		if (findCycle(u, v)) return true;
	}
	return false;
}

// ############################################################### //
// Encontrar ciclo en un grafo dirigido (retorna de longitud 2)
bool findCycleDir(int v, int p){
	visited[v] = VISITANDO;
	parent[v] = p;

	for (int u : outEdges[v]){
		if (visited[u] == NO_VISITADO){
			if (findCycleDir(u, v)) return true;
		} else if (visited[u] == VISITANDO){
			cycle_start = u;
			cycle_end = v;
			return true;
		}
	}

	visited[v] = VISITADO;
	return false;
}
