const int N = 1e7;
int info[N], lch[N], rch[N];
int c1 = 2;
int root_of_version[N];
int c2 = 1;
class PersistentSegmentTree
{
    int n;
    int clone(int p) {
        int i = c1++;
        info[i] = info[p];
        lch[i] = lch[p];
        rch[i] = rch[p];
        return i;
    }
    #define SETM int m = (l + r) / 2;
    #define CLONE int t = clone(lch[p]); lch[p] = t; \
        t = clone(rch[p]); rch[p] = t;
    #define LEFT l, m, lch[p]
    #define RIGHT m+1, r, rch[p]
    #define PULL pull(p);
    void pull(int p) { info[p] = info[lch[p]] + info[rch[p]]; }
    void build(int l, int r, int p) {
        if (l == r) return;
        SETM CLONE
        build(LEFT);
        build(RIGHT);
    }
    void add(int i, int x, int l, int r, int p) {
        if (l == r) { info[p] += x; return; }
        SETM CLONE 
        if (i <= m) add(i, x, LEFT);
        if (i > m) add(i, x, RIGHT);
        PULL
    }
    int get(int i, int l, int r, int p) {
        if (l == r) return info[p];
        SETM
        if (i <= m) return get(i, LEFT);
        if (i > m) return get(i, RIGHT);
    }
    int get_kth(int k, int l, int r, int p1, int p2) {
        if (l == r) return l;
        SETM 
        int dif = info[lch[p2]] - info[lch[p1]];
        if (dif >= k)
            return get_kth(k, l, m, lch[p1], lch[p2]);
        else
            return get_kth(k - dif, m+1, r, rch[p1], rch[p2]);
    }
public:
    PersistentSegmentTree(int n) : n(n) {
        root_of_version[0] = 1;
        build(1, n, 1);
    }
    void inc(int i) {
        int p = clone(root_of_version[c2 - 1]);
        add(i, 1, 1, n, p);
        root_of_version[c2++] = p;
    }
    int get_kth(int i, int j, int k) {
        int p1 = root_of_version[i - 1];
        int p2 = root_of_version[j];
        return get_kth(k, 1, n, p1, p2);
    }
}; // static range kth