// BFS Normal
void bfs(ll inicio, vector<vector<ll>> &ady, vector<bool> &vis, vector<ll> &parent){
    queue<ll> q;
    q.push(inicio);
    vis[inicio] = true;
    while(!q.empty()){
        ll v = q.front();  // v es el vertice que estoy procesando
        q.pop();
        for (ll u : ady[v]){
            if (!vis[u]){
                vis[u] = true;
                parent[u] = v;
                q.push(u);
            }
        }
    }
}

// BFS que calcula los padres de los vertices
void calculatingParents(ll v, vector<vector<ll>> &adjList, vector<bool> &visited, vector<ll> &parents){
    ll n = adjList.size();
    visited[v] = true;
    parents[v] = v;

    queue<ll> q;
    q.push(v);

    while (!q.empty()){
        ll u = q.front();
        q.pop();

        for (int i = 0; i < adjList[u].size(); i++){
            ll w = adjList[u][i];
            if (!visited[w]){
                parents[w] = u;
                visited[w] = true;
                q.push(w);
            }
        }
    }
}

// BFS que chequea si un grafo es bipartito
bool isBipartite(ll v, vector<vector<ll>> &adjList, vector<ll> &teams){
    bool res = true;
    ll n = adjList.size();
    teams[v] = 1;

    queue<ll> q;
    q.push(v);

    while (!q.empty()){
        ll u = q.front();
        q.pop();

        for (int i = 0; i < adjList[u].size(); i++){
            ll w = adjList[u][i];
            if (teams[w] == 0){ // If the node isn't painted, paint it.
                if (teams[u] == 1){
                    teams[w] = 2;
                } else {
                    teams[w] = 1;
                }
                q.push(w);
            } else {
                if (teams[w] == teams[u]){ // If the node is painted, I check that its color is different from the v.
                    res = false;
                    break;
                }
            }
        }
    }

    return res;
}

// BFS que calcula el numero de componentes conexas
ll numberOfConnectedComponents(vector<vector<ll>> &adjList){
    ll n = adjList.size();
    vector<bool> visited(n, false);
    vector<ll> parents(n, UNDEFINED);
    ll res = 0;

    for (int i = 0; i < n; i++){
        if (!visited[i]){
            bfs(i, adjList, visited, parents);
        }
    }

    return res;
}

// BFS que calcula el numero de vertices en una componente conexa
ll numberOfVerticesInConnectedComponent(ll v, vector<vector<ll>> &adjList){
    ll n = adjList.size();
    vector<bool> visited(n, false);
    visited[v] = true;
    ll res = 1;

    queue<ll> q;
    q.push(v);

    while (!q.empty()){
        ll w = q.front();
        q.pop();

        for (int i = 0; i < adjList[w].size(); i++){
            ll u = adjList[w][i];

            if (!visited[u]){
                q.push(u);
                visited[u] = true;
                res++;
            }
        }
    }

    return res;
}