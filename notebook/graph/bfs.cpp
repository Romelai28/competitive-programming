void bfs(ll inicio, vector<vector<ll>> &ady, vector<bool> &vis, vector<ll> &parent){
    queue<ll> q;
    q.push(inicio);
    vis[inicio] = true;
    while(!q.empty()){
        ll v = q.front();  // v es el vértice que estoy procesando
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