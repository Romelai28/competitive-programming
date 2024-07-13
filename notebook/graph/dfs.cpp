void dfs(ll v, vector<vector<ll>> &ady, vector<bool> &vis){
    vis[v] = true;
    for(ll u : ady[v]){
        if (!vis[u]){
            dfs(u, ady, vis);
        }
    }
}