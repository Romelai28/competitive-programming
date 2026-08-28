const int MAXN = 2e5 + 1;
const int MAXB = 500;
int n, q;
int a[MAXN];
int L[MAXN], R[MAXN];
int block_size;
short bi[MAXN];
int br[MAXB];
int qry[MAXN];
int ans[MAXN];

int rm[MAXN], lm[MAXN];
int _rm[MAXN], _lm[MAXN];
int brute_force(int l, int r) {
    forab(i, l, r) lm[a[i]] = rm[a[i]] = 0;
    forab(i, l, r) {
        if (not lm[a[i]]) lm[a[i]] = i;
        rm[a[i]] = i;
    }
    int ans = 0;
    forab(i, l, r) chmax(ans, rm[a[i]] - lm[a[i]]);
    return ans;
}
struct Window
{
    int l, r;
    int ans;
    int tt;
    void radd(int i) {
        if (not lm[a[i]]) lm[a[i]] = i;
        rm[a[i]] = i;
        chmax(ans, rm[a[i]] - lm[a[i]]);
    }
    void ladd(int i) {
        if (not _rm[a[i]]) _rm[a[i]] = i;
        _lm[a[i]] = i;
        chmax(ans, _rm[a[i]] - _lm[a[i]]);
        chmax(ans, rm[a[i]] - _lm[a[i]]);
    }
    void ldel(int i) {
        _rm[a[i]] = _lm[a[i]] = 0;
    }
    void backup() { tt = ans; }
    void rollback() { ans = tt; }
    void reset(int i) {
        l = i, r = i - 1;
        ans = 0;
        for1(i, coords.size()) lm[i] = rm[i] = 0;
    }
    int query(int i, int j) {
        int I = l;
        while (j > r) radd(++r);
        backup();
        while (i < I) ladd(--I);
        int ret = ans;
        while (I < l) ldel(I++);
        rollback();
        return ret;
    }
} w;

// main
    block_size = sqrt(n);
    for (int i = 1, b = 1; i <= n; i += block_size, b++) {
        br[b] = min(i + block_size - 1, n);
        forab(j, i, br[b]) bi[j] = b;
    }
    for1(i, q) qry[i] = i;
    sort(qry+1, qry+1 + q, [](int i, int j) {
        if (bi[L[i]] == bi[L[j]]) return R[i] < R[j];
        return bi[L[i]] < bi[L[j]];
    });
    
    for (int i = 1, j; i <= q; i = j + 1)
    {
        #define qi (qry[i])
        j = i + 1;
        while (j <= q and bi[L[qry[j]]] == bi[L[qi]]) j++;
        j--;
        
        while (i <= j and bi[L[qi]] == bi[R[qi]])
            ans[qi] = brute_force(L[qi], R[qi]),
            i++;
            
        if (i > j) continue;
        w.reset(br[bi[L[qi]]]);
        while (i <= j)
            ans[qi] = w.query(L[qi], R[qi]),
            i++;
    }