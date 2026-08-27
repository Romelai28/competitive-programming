// Maxima distancia desde cada vertice a otro
// Supongo que adjList[v] solo contiene a los hijos y no al padre
vector<priority_queue<int>> bestDepthsFrom(n); // Te dice las distancias de un vertice a las hojas de su arbol
forn(i, n) bestDepthsFrom[i].push(0);

void initializeMaxDepth(int v, int currentDepth){
	for (int u : adjList[v]){
		parent[u] = v;
		calculateMaxDepth(u, currentDistanceFromRoot+1);
		maxDepthFrom[v] = max(maxDepthFrom[v], maxDepthFrom[u] + 1);
		bestDepthsFrom[v].push(maxDepthFrom[u]+1);
	}
}

void updateMaxDepth(){
	queue<int> q;
	q.push(0);

	while (!q.empty()){
		int v = q.front();
		q.pop();

		if (v != 0 && SIZE(bestDepthsFrom[parent[v]]) > 1){ // Tengo dos opciones. Seleccionar el primer vertice mas lejano a mi padre y unirme a su camino lo que da
			int a = bestDepthsFrom[myParent].top();
			bestDepthsFrom[myParent].pop();
			if (a != maxDepthFrom[v] + 1) bestDepthsFrom[v].push(a+1);
			else bestDepthsFrom[v].push(bestDepthsFrom[myParent].top()+1);					
			bestDepthsFrom[myParent].push(a);
		} else if (v != 0 && SIZE(bestDepthsFrom[parent[v]]) == 1) {
			bestDepthsFrom[v].push(1); // Esto solo ejecuta para n = 2
		}

		for (int u : adjList[v]) q.push(u);
	}
}

// ############################################################### //
// La suma de las distancias de un vertice al resto. Esto calculado para todos los vertices
ll calculateSumDistancesFromRoot(int v, int currentDepth){
	ll res = 0;
	for (int u : adjList[v]) res += currentDepth + calculateSumDistancesFromRoot(u, currentDepth+1);
	return res;
}

sumDistances[0] = calculateSumDistancesFromRoot(0, 1); 
subtreeSize(n, 1);

void updateSumDistances(int v, int parent){
	if (v != 0){
		ll nodesThatIAmFarNow = (ll) n - subtreeSize[v];
		sumDistances[v] = (ll) sumDistances[parent] - subtreeSize[v] + nodesThatIAmFarNow; 
	}

	for (int u : adjList[v]) updateSumDistances(u, v, res);
}