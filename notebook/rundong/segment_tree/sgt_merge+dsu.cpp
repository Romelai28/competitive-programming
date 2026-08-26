class SegmentTree
{
    #define LEFT lch[p], l, m 
    #define RIGHT rch[p], m + 1, r
    #define SETM int m = (l + r) / 2;
    #define IN_RANGE (i <= l and r <= j)
    void pull(int p) { info[p] = info[lch[p]] + info[rch[p]]; }
public:
    int make_tree(int i, int l=1, int r=n) {
        if (l == r) { info[c1] = 1; return c1++; }
        SETM
        int p = c1++;
        if (i <= m) lch[p] = make_tree(i, l, m);
        if (i > m) rch[p] = make_tree(i, m + 1, r);
        pull(p);
        return p;
    }
    int merge(int p1, int p2) {
        if (p1 == nil or p2 == nil) return p1 + p2;
        info[p1] += info[p2];
        lch[p1] = merge(lch[p1], lch[p2]);
        rch[p1] = merge(rch[p1], rch[p2]);
        return p1;
    }
    int kth(int k, int p, int l=1, int r=n) {
        if (l == r) return l;
        SETM
        if (k <= info[lch[p]]) return kth(k, LEFT);
        return kth(k - info[lch[p]], RIGHT);
    }
} st;

class DSU {
    vi f, s, t;
public:
    DSU(int n) : f(n+1), s(n+1, 1), t(n+1) {
        for1(i, n) f[i] = i;
        for1(i, n) t[i] = st.make_tree(p[i]);
    }
    int find(int i) { return i == f[i] ? i : f[i] = find(f[i]); }
    bool unite(int i, int j) {
        i = find(i); j = find(j);
        if (i == j) return false;
        if (s[i] > s[j]) swap(i, j);
        f[i] = j;
        s[j] += s[i];
        t[j] = st.merge(t[i], t[j]);
        return true;
    }
    int tree(int i) { return t[find(i)]; }
};