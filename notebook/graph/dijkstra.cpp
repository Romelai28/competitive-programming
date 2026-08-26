using peso_t = ll;
using nodo_pesado_t = pair<peso_t, int>;  // {weight, to}
using wgraph_t = vv<nodo_pesado_t>;

// Sparse graph. O(m*log(n))
vl dijkstra(int s, wgraph_t &ady){
    vl dist(SIZE(ady), LINF);
    // vi parent(SIZE(ady), UNDEFINED);
    vb vis(SIZE(ady), false);
    set<nodo_pesado_t> q;

    dist[s] = 0;
    q.insert({0, s});

    while(!q.empty()){
        int v = q.begin() -> snd;
        q.erase(q.begin());
        
        if (vis[v]) {continue;}
        vis[v] = true;
        for(auto [w, u] : ady[v]){
            if(dist[v] + w < dist[u]){
                q.erase({dist[u], u});
                dist[u] = dist[v] + w;
                // parent[u] = v;
                q.insert({dist[u], u});
            }
        }
    }
    return dist;
}