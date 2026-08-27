enum ESTADO {
	VISITADO_AHORA,
	VISITADO_ANTES,
	NO_VISITADO
};

struct SuccesorGraph{
	vi succesors;
	BinaryJumping BJ;
	vector<ESTADO> visited;
	vi representantOfVertex;
	vi rootOfTree;
	vi distanceFromRoot;
	vi distanceFromRepresentant;
	vi lengthOfCycleAt;
	vector<vi> adjList;
	
	
	SuccesorGraph(vi &succ) : succesors(succ), BJ(succ, SIZE(succ)){
		visited.resize(SIZE(succ), NO_VISITADO);
		representantOfVertex.resize(SIZE(succ), UNDEFINED);
		rootOfTree.resize(SIZE(succ), UNDEFINED);
		distanceFromRoot.resize(SIZE(succ), UNDEFINED);
		distanceFromRepresentant.resize(SIZE(succ), UNDEFINED);
		lengthOfCycleAt.resize(SIZE(succ), UNDEFINED);	
		adjList.resize(SIZE(succ));
		forn(i, SIZE(succ)) adjList[succ[i]].pb(i);
		findCycles();
	}
	
	int distanceInTheCycle(int v, int u){
		// Se que los dos vertices pertenecen al mismo ciclo y quiero calcular cual es su distancia
		int res = distanceFromRepresentant[u] - distanceFromRepresentant[v]; // v -> ... -> u
		if (distanceFromRepresentant[u] < distanceFromRepresentant[v]){ // v -> ... inicio ciclo -> ... -> u
			int longitudCiclo = lengthOfCycleAt[representantOfVertex[v]];
			res = distanceFromRepresentant[u] + (longitudCiclo - distanceFromRepresentant[v]) + 1; 
		} 
	
		return res;
	}
	
	int distanceBetween(int v, int u){
		int rootOfV = rootOfTree[v], rootOfU = rootOfTree[u];
		int res;
		
		if (representantOfVertex[rootOfV] != representantOfVertex[rootOfU]) res = UNDEFINED; // Si no estan en el mismo ciclo
		else if (rootOfV == rootOfU){ // Estan en el mismo arbol		
			int jumps = distanceFromRoot[v] - distanceFromRoot[u];
			int vertexJumpt = BJ.succ_k(v, jumps);
			if (vertexJumpt != u) jumps = -1;
			res = jumps;
		} else if (representantOfVertex[u] == UNDEFINED) res = UNDEFINED; // u y v estan en arboles distintos
		else res = distanceFromRoot[v] + distanceInTheCycle(rootOfV, rootOfU);
		
		return res;
	}
	
	void dfs(int v, vector<int> &representantsOfCycles){
		visited[v] = VISITADO_AHORA;
		
		if (visited[succesors[v]] == VISITADO_AHORA){
			representantsOfCycles.pb(succesors[v]);
			visited[v] = VISITADO_ANTES;
			return ;
		} else if (visited[succesors[v]] == VISITADO_ANTES){
			visited[v] = VISITADO_ANTES;
			return ;
		}
		
		dfs(succesors[v], representantsOfCycles);
		visited[v] = VISITADO_ANTES;
	}
	
	void markCycle(int v){
		int lengthOfCycle = 0, startCycle = v;
		
		while (representantOfVertex[v] == UNDEFINED){
			representantOfVertex[v] = startCycle;
			distanceFromRepresentant[v] = lengthOfCycle;
			v = succesors[v];
			lengthOfCycle++;
		}
		
		lengthOfCycleAt[startCycle] = lengthOfCycle - 1;
	}
	
	void buildTree(int v, int currentDepth, int root){
		rootOfTree[v] = root;
		distanceFromRoot[v] = currentDepth;
		for (int u : adjList[v]) if (representantOfVertex[u] == UNDEFINED) buildTree(u, currentDepth+1, root);
	}
	
	void findCycles(){
		vi representantsOfCycles;
		forn(i, SIZE(succesors)) if (visited[i] == NO_VISITADO) dfs(i, representantsOfCycles);
		for (int v : representantsOfCycles) markCycle(v);
		forn(i, SIZE(succesors)) if (representantOfVertex[i] != UNDEFINED) buildTree(i, 0, i);
	}
};