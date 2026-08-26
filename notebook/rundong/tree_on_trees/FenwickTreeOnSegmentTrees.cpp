const int N = 3e7;
int lch[N], rch[N];
const int nil = 0;
int c1 = 1;
int info[N];
class SegmentTree {
    #define GET(X) ((X) == nil ? (X) = c1++ : (X))
    #define SETM int m = (l + r) / 2;
    #define PULL pull(p);
    void pull(int p) { info[p] = info[lch[p]] + info[rch[p]]; }
    void add(int i, int x, int p, int l, int r) {
        if (l == r) { info[p] += x; return; }
        SETM
        if (i <= m) add(i, x, GET(lch[p]), l, m);
        if (i > m) add(i, x, GET(rch[p]), m + 1, r);
        PULL 
    }
public:
    int root = nil;
    void insert(int x) { add(x, 1, GET(root), 1, coords.size()); }
    void erase(int x) { add(x, -1, GET(root), 1, coords.size()); }
};


SegmentTree t[MAXN];
class FenwickTree {
    #define lowbit(x) ((x) & -(x))
    void get_segment_trees(int i, vi& out) {
        while (i) out.push_back(t[i].root), i -= lowbit(i);
    }
    vi& go_left(vi& ps) {
        for (int& p : ps) p = lch[p];
        return ps;
    }
    vi& go_right(vi& ps) {
        for (int& p : ps) p = rch[p];
        return ps;
    }
    int find_by_order(int k, vi& lps, vi& rps, int l, int r) {
        if (l == r) return l;
        SETM
        int s1 = 0, s2 = 0;
        for (int p : lps) s1 += info[lch[p]];
        for (int p : rps) s2 += info[lch[p]];
        if (k < s2 - s1) return find_by_order(k,
            go_left(lps), go_left(rps), l, m);
        else return find_by_order(k - (s2 - s1),
            go_right(lps), go_right(rps), m + 1, r);
    }
    int order_of_key(int x, vi& lps, vi& rps, int l, int r) {
        if (l == r) return 0;
        SETM
        int s1 = 0, s2 = 0;
        for (int p : lps) s1 += info[lch[p]];
        for (int p : rps) s2 += info[lch[p]];
        if (x <= m) return order_of_key(x,
            go_left(lps), go_left(rps), l, m);
        else return s2 - s1 + order_of_key(x,
            go_right(lps), go_right(rps), m + 1, r);
    }
public:
    void insert(int i, int x) {
        for (int j = i; j <= n; j += lowbit(j))
            t[j].insert(a[i]);
    }
    void modify(int i, int x) {
        for (int j = i; j <= n; j += lowbit(j))
            t[j].erase(a[i]);
        a[i] = x;
        for (int j = i; j <= n; j += lowbit(j))
            t[j].insert(a[i]);
    }
    int find_by_order(int i, int j, int k) {
        vi lps, rps;
        get_segment_trees(i - 1, lps);
        get_segment_trees(j, rps);
        return find_by_order(k, lps, rps, 1, coords.size());
    }
    int order_of_key(int i, int j, int x) {
        vi lps, rps;
        get_segment_trees(i - 1, lps);
        get_segment_trees(j, rps);
        return order_of_key(x, lps, rps, 1, coords.size());
    }
    int pre_lower_bound(int i, int j, int x) {
        int k = order_of_key(i, j, x);
        if (k == 0) return 1;
        return find_by_order(i, j, k - 1);
    }
    int upper_bound(int i, int j, int x) {
        int k = order_of_key(i, j, x + 1);
        if (k == j - i + 1) return coords.size();
        return find_by_order(i, j, k);
    }
} ft;