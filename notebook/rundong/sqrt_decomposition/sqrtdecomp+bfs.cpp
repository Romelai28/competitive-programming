int sorted[MAXN];
int maxm[MAXB];
auto cmp_dist = [](int i, int j) {
    return dist2(y[i], x[i]) < dist2(y[j], x[j]);
};
void build() {
    block_size = sqrt(n);
    for (int i = 1, b = 1; i <= n; i += block_size, b++) {
        bl[b] = i;
        br[b] = min(n, i + block_size - 1);
        for (int j = i; j <= br[b]; ++j) bi[j] = b;
    }
    for1(i, n) sorted[i] = i;
    sort(sorted + 1, sorted + 1 + n, [&](int i, int j) {
        return m[i] < m[j];
    });
    for (int b = 1; br[b]; ++b) {
        maxm[b] = m[sorted[br[b]]];
        sort(sorted + bl[b], sorted + br[b] + 1, cmp_dist);
    }
}
bool vis[MAXN];
int solve()
{
    build();
    int ans = 0;
    vi que = { 0 };
    while (not que.empty()) {
        vi ext;
        for (int i : que)
        {
            ll r2 = (ll)r[i] * r[i];
            int b = 1;
            int v;
            for (; br[b] and maxm[b] <= p[i]; ++b) {
                while (v = sorted[bl[b]], bl[b] <= br[b] and
                    dist2(y[v], x[v]) <= r2)
                {
                    if (vis[v]) { bl[b]++; continue; }
                    ext.push_back(v),
                    ans++,
                    bl[b]++;
                }
            }
            if (br[b])
            for (int j = bl[b], v = sorted[j]; j <= br[b] and
                dist2(y[v], x[v]) <= r2; ++j, v = sorted[j])
            {
                if (not vis[v] and m[v] <= p[i]) {
                    ext.push_back(v);
                    ans++;
                    vis[v] = true;
                }
            }
        }
        swap(ext, que);
    }
    return ans;
}