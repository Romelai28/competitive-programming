using Edge = pair<int, int>;

struct Tarjan{
	vector<vi> adjList;
	vb visited;
	vi foundAt, minTimeFound;
	vector<Edge> bridges;
	
	Tarjan(vector<vi> &adj) : adjList(adj){
		visited.resize(SIZE(adjList), false);
		foundAt.resize(SIZE(adjList));
		minTimeFound.resize(SIZE(adjList));
	}
	
	// Llamarlo con parent = UNDEFINED
	void dfs(int v, int currentTime, int parent){
		visited[v] = true;
		foundAt[v] = minTimeFound[v] = currentTime;
		
		for (int w : adjList[v]) if (w != parent){			
			if (!visited[w]) {
				dfs(w, currentTime+1, v);
				minDepth[v] = min(minDepth[v], minDepth[w]); 
			} else minDepth[v] = min(minDepth[v], depth[u]);
		}

		if (parent != -1 && minDepth[v] > depth[p]) bridges.insert(make_pair(v, p));
	}

	// Para AP
	void dfs(int v, int p, vi &depth, vi &minDepth){
		if (p != -1) depth[v] = depth[p] + 1;
		minDepth[v] = depth[v];
		int children = 0;
		for (int u : adj[v]) if (u != p){ 
			if (minDepth[u] == UNDEFINED){ 
				dfs(u, v, depth, minDepth), children++;
				minDepth[v] = min(minDepth[v], minDepth[u]); 
				if (minDepth[u] >= depth[v] && p != -1) ap.insert(v); 
			} else minDepth[v] = min(minDepth[v], depth[u]);
		}
		
		if (p == -1 && children > 1) ap.insert(v); // Si la raiz tiene 2 hijos o mas, es punto de articulacion
	}
};
