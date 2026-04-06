int floor_log2(int x){
    assert(x > 0);
    return 31 - __builtin_clz(x);
}

struct LCA {
    int N, LOGN, ROOT;
    vi depth;
    vvi up, adj;

    LCA(int n, int root, vvi &ADJ) : N(n), LOGN(floor_log2(n) + 1), ROOT(root), depth(n), up(LOGN, vi(n, -1)), adj(ADJ) {
        dfs(ROOT, -1);
        forn(k, LOGN - 1) forn(v, N) if (up[k][v] != -1) up[k + 1][v] = up[k][up[k][v]];
    }

    void dfs(int v, int p) {
        up[0][v] = p;
        for (int u : adj[v]) if (u != p) {
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
    }

    int climb(int v, int d) {
        assert(depth[v] >= d);
        dforn(k, LOGN) if ((d >> k) & 1) v = up[k][v];
        return v;
    }

    int lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        a = climb(a, depth[a] - depth[b]);
        if (a == b) return a;
        dforn(k, LOGN) if (up[k][a] != up[k][b]) a = up[k][a], b = up[k][b];
        return up[0][a];
    }

    int dist(int a, int b) {
        return depth[a] + depth[b] - 2 * depth[lca(a, b)];
    }
};

/*
For a successor graph:
- Remove ROOT, depth, adj, dfs(), lca() and dist()
- Initialize up as: forn(v, N) up[0][v] = nxt[v];
- up[k + 1][v] = up[k][up[k][v]];
- Use LOGN = 60.
*/