class SegmentTree {
    #define GET(X) ((X) == nil ? (X) = make_node() : (X))
    #define LEFT GET(lch[p]), l, m 
    #define RIGHT GET(rch[p]), m+1, r 
    #define SETM int m = (l + r) / 2;
    #define IN_RANGE (i <= l and r <= j)
    #define PULL pull(p);
    void pull(int p) { info[p] = info[lch[p]] + info[rch[p]]; }
public:
    void add(int i, ll x, int p, int l=0, int r=n) {
        if (l == r) { info[p] += x; return; }
        SETM 
        if (i <= m) add(i, x, LEFT);
        if (i > m) add(i, x, RIGHT);
        PULL 
    }
    ll query(int i, int j, int p, int l=0, int r=n) {
        if IN_RANGE return info[p];
        SETM
        ll ans = 0;
        if (i <= m) ans += query(i, j, lch[p], l, m);
        if (j > m) ans += query(i, j, rch[p], m+1, r);
        return ans;
    }
} sgt;
int cpa[MAXN];
int add_sgt[MAXN];
int minus_sgt[MAXN];
void centroid_decomposition(int c) {
    vis[c] = true;
    for_adj(u, c) if (not vis[u]) {
        int c2 = get_centroid(u, c);
        cpa[c2] = c;
        centroid_decomposition(c2);
    }
}
void add(int v, ll x) {
    sgt.add(0, x, GET(add_sgt[v]));
    for (int cur = v, pa = cpa[cur]; pa; cur = pa, pa = cpa[cur]) {
        int dist = get_dist(v, pa);
        sgt.add(dist, x, GET(add_sgt[pa]));
        sgt.add(dist, x, GET(minus_sgt[cur]));
    }
}
ll query(int v, int d) {
    ll ans = sgt.query(0, d, add_sgt[v]);
    for (int cur = v, pa = cpa[cur]; pa; cur = pa, pa = cpa[cur]) {
        int dist = get_dist(v, pa);
        if (dist <= d) {
            ans += sgt.query(0, d - dist, add_sgt[pa]);
            ans -= sgt.query(0, d - dist, minus_sgt[cur]);
        }
    }
    return ans;
}
//main
    for1(v, n) add(v, val[v]);
    ll lastans = 0;
    repeat(m)
    {
        ll op, x, k;
        #define y (k)
        cin >> op >> x >> k;
        x ^= lastans; k ^= lastans;
        if (op == 0) {  // op0: suma de peso de todos los puntos a distancia <= k de x
            lastans = query(x, k);
            cout << lastans << '\n';
        } else {  // op1: modificar el peso de x a ser y
            add(x, -val[x]);
            val[x] = y;
            add(x, val[x]);
        }
    }
