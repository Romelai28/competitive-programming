void bfs(int v, vb &visited, vector<vi> &outEdges){
	visited[v] = VISITANDO;
	queue<int> q;
	q.push(v);
	while(!q.empty()){
		int u = q.front(); q.pop();
		for (int w : outEdges[u]){
			if (visited[w] == NO_VISITADO){
				visited[w] = VISITANDO;
				q.push(w);
			}
		}
		visited[u] = VISITADO;
	}
}