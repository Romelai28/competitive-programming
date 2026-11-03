int make_node(int x) {
    int i = c1++; key[i] = x; sz[i] = 1;
    return i;
}
int clone(int p) {
    if (p == nil) return nil;
    int i = c1++;
    key[i] = key[p]; lch[i] = lch[p]; rch[i] = rch[p]; sz[i] = sz[p];
    return i;
}
class PersistentFHQTreap {
    #define CLONE(X) ((X) = clone(X))
    void up(int i) { sz[i] = sz[lch[i]] + 1 + sz[rch[i]]; }
    void split(int l, int r, int i, int k) {
        if (i == nil) { rch[l] = lch[r] = nil; return; }
        if (sz[lch[i]] + 1 <= k) {
            rch[i] = clone(rch[i]);
            rch[l] = i;
            split(i, r, rch[i], k - sz[lch[i]] - 1);
        } else {
            lch[i] = clone(lch[i]);
            lch[r] = i;
            split(l, i, lch[i], k);
        }
        up(i);
    }
public:
    ii split(int i, int k) {
        i = clone(i);
        split(0, 0, i, k);
        ii ret = { rch[0], lch[0] };
        rch[0] = lch[0] = 0;
        return ret;
    }
    int merge(int l, int r) {
        if (l == nil or r == nil) { return l | r; }
        if (rng() % (sz[l] + sz[r]) < sz[l]) {  // mt19937_64
            CLONE(l);
            rch[l] = merge(rch[l], r);
            up(l); return l;
        } else {
            CLONE(r);
            lch[r] = merge(l, lch[r]);
            up(r); return r;
        }
    }
    int push_back(int x, int t) { t = merge(t, make_node(x)); return t; }
    int size(int i) { return sz[i]; }
    int front(int t) { return lch[t] ? front(lch[t]) : key[t]; }
} fhq;

vector<int> ans;
//main: Summer Vacation solution
    cin >> n;
    for1(i, n) cin >> a[i];
    int dp = nil;
    int S = 2*n+1;
    for (int i = 0; i < S; ++i) dp = fhq.push_back(i, dp);
    for (int i = n; i >= 1; --i) {
        auto [_1, t1] = fhq.split(dp, a[i]);
        auto [pre, _2] = fhq.split(t1, a[i]);
        auto [suf, _3] = fhq.split(dp, fhq.size(dp) - a[i]);
        dp = fhq.merge(pre, suf);
        cout << fhq.front(dp) << ' ';
    }