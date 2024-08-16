// DFS simple
void dfs(ll v, vector<vector<ll>> &ady, vector<bool> &vis){
    vis[v] = true;
    for(ll u : ady[v]){
        if (!vis[u]){
            dfs(u, ady, vis);
        }
    }
}

// DFS que me dice si existe un ciclo en un grafo (no dirigido) y en caso de existir, retorna la back-edge
pair<bool, edge> hasCycle(int v, vector<vector<int>> &adjList, vector<bool> &visited, vector<int> &parents){ 
    visited[v] = true;
    edge e = {UNDEFINED, UNDEFINED};
    pair<bool, edge> res = {false, e};

    for (int i = 0; i < adjList[v].size(); i++){
        int w = adjList[v][i];
        if (!visited[w]){
            parents[w] = v;
            res = hasCycle(w, adjList, visited, parents);
            if (res.first){
                break;
            }
        } else if (visited[w] && parents[v] != w && parents[v] != UNDEFINED){
            edge backEdge = {w,v};
            return {true, backEdge};
        }
    }

    return res;
}