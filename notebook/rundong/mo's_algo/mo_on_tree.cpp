bool vis[MAXN];
int freq[MAXN];
struct Window {
    int l = 1, r = 0;
    int ans = 0;
    void flip(int i) {
        if (vis[vtx[i]]) {
            vis[vtx[i]] = false;
            if (--freq[a[vtx[i]]] == 0) ans--;
        } else {
            vis[vtx[i]] = true;
            if (freq[a[vtx[i]]]++ == 0) ans++;
        }
    }
    int query(int i, int j, int lca) {
        while (i < l) flip(--l);
        while (j > r) flip(++r);
        while (i > l) flip(l++);
        while (j < r) flip(r--);
        if (lca) {
            flip(vs[lca]);
            int ret = ans;
            flip(vs[lca]);
            return ret;
        } else
            return ans;
    }
} w;

// main
    for1(i, q) {
        cin >> u >> v;
        if (vs[u] > vs[v]) swap(u, v);
        int l = lca(u, v);
        if (l == u) L[i] = vs[u], R[i] = vs[v];
        else L[i] = ve[u], R[i] = vs[v], A[i] = l;
    }
    block_size = sqrt(2 * n);
    for (int i = 1, b = 1; i <= 2 * n; i += block_size, b++) {
        int br = min(i + block_size - 1, 2 * n);
        forab(j, i, br) bi[j] = b;
    }
    for1(i, q) qry[i] = i;
    sort(qry+1, qry+1 + q, [](int i, int j) {
        if (bi[L[i]] != bi[L[j]]) return bi[L[i]] < bi[L[j]];
        if (bi[L[i]] % 2) return R[i] < R[j];
        else return R[i] > R[j];
    });
    for1(i, q)
    {
        int qi = qry[i];
        ans[qi] = w.query(L[qi], R[qi], A[qi]);
    }