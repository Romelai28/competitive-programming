// adj[v][0] es el hijo pesado de v, si existe
// head[v] te dice cual es el primer vertice del camino pesado de v
// pos[v] te dice la posicion de v en el segment tree
// subtree(v) = [pos[v], pos[v] + sz[v] - 1]
// Los caminos pesados y subtrees quedan como intervalos contiguos

struct HLD{
    int n, root, curPos = 0;
    vi parent, depth, head, pos, sz;
    vvi adj;

    HLD(vvi ADJ, int ROOT = 0) : n(SIZE(ADJ)), root(ROOT), adj(ADJ) {
        parent.assign(n, -1);
        depth.assign(n, 0);
        head.assign(n, 0);
        pos.assign(n, 0);
        sz.assign(n, 0);

        parent[root] = root;
        dfs(root);
        decompose(root, root);
    }

    void dfs(int v){
        sz[v] = 1;
        for (int &u : adj[v]){
            parent[u] = v; depth[u] = depth[v] + 1;
            adj[u].erase(find(all(adj[u]), v)); 
            dfs(u); sz[v] += sz[u];
            if (sz[u] > sz[adj[v][0]]) swap(u, adj[v][0]);
        }
    }

    void decompose(int v, int h){
        head[v] = h; pos[v] = curPos++;
        for (int u : adj[v]) decompose(u, u == adj[v][0] ? h : u);
    }

    pair<int,int> subtree(int v){ return {pos[v], pos[v] + sz[v] - 1}; }
};

// Modificar segun que funcion estes aplicando
int query(int a, int b, HLD &H, SegmentTree &T){
	int res = 0;
    for (; H.head[a] != H.head[b]; b = H.parent[H.head[b]]){
		if (H.depth[H.head[a]] > H.depth[H.head[b]]) swap(a, b);
        int query_heavy_path = T.query(H.pos[H.head[b]], H.pos[b]);
        res = max(res, query_heavy_path);
    }
    
    if (H.depth[a] > H.depth[b]) swap(a, b);
    int last_query_heavy_path = T.query(H.pos[a], H.pos[b]);
    return res = max(res, last_query_heavy_path);
}