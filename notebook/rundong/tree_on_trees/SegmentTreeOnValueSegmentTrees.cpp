const int nil = 0;
const int N = 2e7;
int lch[N], rch[N];
ll info[N], tag[N];
int c1 = 1;
class SegmentTree {
    
    int n;
    int root;
    
    int make_node() {
        int i = c1++;
        return i;
    }
    void pull(int p) { info[p] = info[lch[p]] + info[rch[p]]; }
    
    #define SETM int no, m = l + (r - l) / 2;
    #define LEFT l, m, lch[p] == nil ? \
        (no = make_node(), lch[p] = no) : lch[p]
    #define RIGHT m+1, r, rch[p] == nil ? \
        (no = make_node(), rch[p] = no) : rch[p]
    #define IN_RANGE (i <= l and r <= j)
    #define PULL pull(p);
    #define PUSH push(l, r, p);
    
    void lazy_add(ll x, int l, int r, int p) {
        info[p] += (r - l + 1) * x;
        tag[p] += x;
    }
    
    void push(int l, int r, int p) {
        if (tag[p]) {
            SETM
            lazy_add(tag[p], LEFT);
            lazy_add(tag[p], RIGHT);
            tag[p] = 0;
        }
    }
    
    void add(int i, int j, ll x, int l, int r, int p) {
        if IN_RANGE { lazy_add(x, l, r, p); return; }
        SETM PUSH 
        if (i <= m) add(i, j, x, LEFT);
        if (j > m) add(i, j, x, RIGHT);
        PULL 
    }
    
    ll query(int i, int j, int l, int r, int p) {
        if IN_RANGE return info[p];
        SETM PUSH 
        ll ans = 0;
        if (i <= m) ans += query(i, j, LEFT);
        if (j > m) ans += query(i, j, RIGHT);
        return ans;
    }
    #define GET_ROOT if (root == nil) root = make_node();
    
public:
    SegmentTree(int n) : n(n), root(nil) {}
    void add(int i, int j, ll x) { GET_ROOT add(i, j, x, 1, n, root); }
    ll query(int i, int j) { GET_ROOT return query(i, j, 1, n, root); }
};

class NestedSegmentTree {
    int n;
    vector<SegmentTree> info;
    #undef LEFT
    #undef RIGHT
    #define LEFT l, m, 2*p 
    #define RIGHT m+1, r, 2*p+1 
    void inc(int ul, int ur, int i, int l, int r, int p) {
        if (l == r) { info[p].add(ul, ur, 1);
        return; }
        SETM
        if (i <= m) inc(ul, ur, i, LEFT);
        if (i > m) inc(ul, ur, i, RIGHT);
        info[p].add(ul, ur, 1);
    }
    int query(int ul, int ur, ll k, int l, int r, int p) {
        if (l == r) return l;
        SETM
        ll rcnt = info[2*p+1].query(ul, ur);
        if (rcnt < k)
            return query(ul, ur, k - rcnt, LEFT);
        if (rcnt >= k)
            return query(ul, ur, k, RIGHT);
    }
public:
    NestedSegmentTree(int n) : n(n),
        info(8*n+10, SegmentTree(n)) {}
    void inc(int ul, int ur, int c) { inc(ul, ur, c + n+1, 1, 2*n+1, 1); }
    int query(int ul, int ur, ll k) { return query(ul, ur, k, 1, 2*n+1, 1) - (n+1); }
};