vector<vector<int>> memo(n, vector<int>(2, 0));
// memo[i][0] means that the vertex i is free, so I can decide if I want to use it
// memo[i][1] means that the vertex i is already used by its father, so I can't use any edge of and all its children will be free

// Suppose that the adjList[v] doesn't include parent[v] and just contain the children of v

int treeMatching(){
	dforn(i, lastLevel+1){ 
		for (auto v : nodesPerLevel[i]){
			for (auto u : adjList[v]) memo[v][1] += memo[u][0]; // I can't use (u, v) never so u will be free
			// I choose the best possible edge (u, v). All the rest vertices will be free except for u
			for (auto u : adjList[v]) memo[v][0] = max(memo[v][0], 1 + memo[v][1] - memo[u][0] + memo[u][1]);
		}
	}
	
	return memo[0][0]; // Return the max amount of matching for a rooted tree in 0
}

