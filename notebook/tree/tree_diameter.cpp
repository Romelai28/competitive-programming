int farthestVertex(int src){
	visited.assign(n, false);
	distances.assign(n, INF);

	queue<int> q;
	q.push(src);
	visited[src] = true;
	distances[src] = 0;

	int farthest = src;

	while (!q.empty()){
		int v = q.front(); q.pop();
		if (distances[v] > distances[farthest]) farthest = v;

		for (int u : adjList[v]){
			if (!visited[u]){
				visited[u] = true;
				distances[u] = distances[v] + 1;
				q.push(u);
			}
		}
	}

	return farthest;
}

int diameterTree(){
	int a = farthestVertex(0);
	int b = farthestVertex(a);
	return distances[b];
}