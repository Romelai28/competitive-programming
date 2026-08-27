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
		
		for (int w : adjList[v]){
			if (w == parent) continue;
			
			if (!visited[w]) {
				dfs(w, currentTime+1, v);
				// Quiere decir que w no llego a v ni a ninguno de sus ancestros
				if (foundAt[v] < minTimeFound[w]) bridges.pb({v, w});
			}
			
			minTimeFound[v] = min(minTimeFound[v], minTimeFound[w]);
		}
	}
};
