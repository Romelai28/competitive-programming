int blen, bnum;
bool mark[MAXN];
short bi[MAXN];
int vtx[MAXB];
Bitset info[MAXB];
short top[MAXB];

void get_vertex(int b) {
    static mt19937 rng(random_device{}());
    static uniform_int_distribution<> random_vertex(1, n);
    
    int pick;
    while (mark[pick = random_vertex(rng)]);
    mark[pick] = true;
    bi[pick] = b;
    vtx[b] = pick;
}

void build() {
    dfs(1, 0, 1);
    for1(i, __lg(n)) for1(v, n) st[i][v] = st[i - 1][st[i - 1][v]];
    
    blen = sqrt(n * 10);
    bnum = n / blen + (bool)(n % blen);
    for1(b, bnum) get_vertex(b);
    for1(b, bnum) {
        int v = vtx[b];
        info[b][a[v]] = 1;
        while (v = parent[v], v and not mark[v])
            bi[v] = b,
            info[b][a[v]] = 1;
        if (v) top[b] = bi[v];
    }
}

Bitset ans;
void query(int x, int l) {
    while (not mark[x] and x != l) ans[a[x]] = 1, x = parent[x];
    if (x == l) return;
    int b = bi[x];
    while (top[b] and dep[vtx[top[b]]] >= dep[l])
        ans |= info[b], b = top[b];
    x = vtx[b];
    while (x != l) ans[a[x]] = 1, x = parent[x];
}