int prv[MAXN], nxt[MAXN];
struct LinkedList {
    ll ans = 0;
    inline int dist(int i, int j) {
        if (i == 0 or j == 0) return 0;
        return abs(pos[i] - pos[j]);
    }
    void link(int i, int j) {
        prv[j] = i;
        nxt[i] = j;
    }
    void insert_after(int i, int j) {
        ans += dist(i, j);
        link(i, nxt[j]);
        link(j, i);
    }
    inline void erase(int i) {
        int p = prv[i], n = nxt[i];
        ll d1, d2, d3;
        d1 = p ? abs(pos[p] - pos[i]) : 0;
        d2 = n ? abs(pos[i] - pos[n]) : 0;
        d3 = p and n ? abs(pos[p] - pos[n]) : 0;
        ans += d3 - d1 - d2;
        nxt[p] = n;
        prv[n] = p;
    }
    inline void rollback(int i) {
        int p = prv[i], n = nxt[i];
        ll d1, d2, d3;
        d1 = p ? abs(pos[p] - pos[i]) : 0;
        d2 = n ? abs(pos[i] - pos[n]) : 0;
        d3 = p and n ? abs(pos[p] - pos[n]) : 0;
        ans += d1 + d2 - d3;
        nxt[p] = i;
        prv[n] = i;
    }
    inline void rollback_(int i) {
        prv[nxt[i]] = i;
        nxt[prv[i]] = i;
    }
} lis;

int block_size;
short bi[MAXN];
int bl[MAXB];
int qry[MAXN];
ll ans[MAXN];

struct Window {
    int l, r;
    ll tmp;
    inline void del(int i) {
        lis.erase(a[i]);
    }
    void reset(int i) {
        while (n > r) lis.rollback_(a[++r]);
        lis.ans = tmp;
        while (i > l) del(l++);
        tmp = lis.ans;
    }
    ll query(int i, int j) {
        while (j < r) del(r--);
        int L = l;
        ll tmp = lis.ans;
        while (L < i) del(L++);
        ll ans = lis.ans;
        while (l < L) lis.rollback_(a[--L]);
        lis.ans = tmp;
        return ans;
    }
} w;

// main
    for1(i, n) pos[a[i]] = i;
    
    for1(i, n) lis.insert_after(i, i - 1);
    block_size = sqrt(n);
    for (int i = 1, b = 1; i <= n; i += block_size, b++) {
        bl[b] = i;
        int br = min(i + block_size - 1, n);
        forab(j, i, br) bi[j] = b;
    }
    for1(i, q) qry[i] = i;
    sort(qry+1, qry+1 + q, [](int i, int j) {
        if (bi[L[i]] != bi[L[j]]) return bi[L[i]] < bi[L[j]];
        return R[i] > R[j];
    });
    
    w.l = 1; w.r = n; w.tmp = lis.ans;
    for (int i = 1, j; i <= q; i = j + 1)
    {
        #define qi (qry[i])
        j = i + 1;
        while (j <= q and bi[L[qry[j]]] == bi[L[qi]]) j++;
        j--;
        
        w.reset(bl[bi[L[qi]]]);
        while (i <= j)
            ans[qi] = w.query(L[qi], R[qi]), i++;
    }