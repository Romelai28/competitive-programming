// Camino mas largo en un DAG desde 0
vi distances(n, -INF);
distances[0] = 0;
vl s = topologicalSort(adjList);

for (int v : s){
    for (int u : adjList[v]){
        if (distances[u] < distances[v] + 1){
            parent[u] = v;
            distances[u] = distances[v] + 1;
        }
    }
}

// Cantidad de caminos desde 0 a otros vertices en un DAG
vector<ll> numberOfPaths(n, 0);
numberOfPaths[0] = 1;

for (int v : s){
    for (int u : adjList[v]) numberOfPaths[u] = addMod(numberOfPaths[u], numberOfPaths[v], MOD);
}
