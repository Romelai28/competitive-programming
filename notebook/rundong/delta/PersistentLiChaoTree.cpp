const int N = 5e7;
const ll RB = 1e9;
const ll LB = -1e9;
int info[N], lch[N], rch[N];
int c1 = 1;
class PersistentLiChaoTree {
    int clone(int p) {
        int i = c1++;
        info[i] = info[p], lch[i] = lch[p], rch[i] = rch[p];
        return i;
    }
    ll _getm(ll l, ll r) {
        const int offset = 1e9 + 7;
        l += offset;
        r += offset;
        ll m = l + (r - l) / 2;
        m -= offset;
        return m;
    }
    #define SETM ll m = _getm(l, r);
    ll eval(int s, int x) {
        ll a = A[s], b = B[s];
        return a * x + b;
    }
    bool better(int s, int t, int x) {
        return eval(s, x) > eval(t, x);
    }
    int lazy(int s, int p, ll l, ll r) {
        p = clone(p);
        if (not info[p]) { info[p] = s; return p; }
        SETM
        if (better(s, info[p], m)) swap(s, info[p]);
        if (better(s, info[p], l)) lch[p] = lazy(s, LEFT);
        if (better(s, info[p], r)) rch[p] = lazy(s, RIGHT);
        return p;
    }
    int query(int x, int p, ll l, ll r) {
        if (l == r) return info[p];
        SETM int ans;
        if (x <= m) ans = query(x, LEFT);
        if (x > m) ans = query(x, RIGHT);
        if (better(info[p], ans, x)) ans = info[p];
        return ans;
    }
public:
    int update(int i, int j, int s, int p, ll l=LB, ll r=RB) {
        if IN_RANGE { p = lazy(s, p, l, r); return p; }
        SETM
        if (i <= m) lch[p] = update(i, j, s, LEFT);
        if (j > m) rch[p] = update(i, j, s, RIGHT);
        return p;
    }
    ll query(int x, int p) {
        int s = query(x, p, LB, RB);
        ll a = A[s], b = B[s];
        return a * x + b;
    }
} sgt;