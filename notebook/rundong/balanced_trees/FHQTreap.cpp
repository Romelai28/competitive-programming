using ii = pair<int, int>;

const int N = 1e7;
int lch[N], rch[N];
const int nil = 0;
int key[N];
int sz[N], prio[N];
int c1 = 1;

int make_node(int x) {
    static random_device rd;
    static mt19937 rng(rd());
    static uniform_int_distribution<> dist(1, 1e9);
    int n = c1++;
    key[n] = x;
    sz[n] = 1; prio[n] = dist(rng);
    return n;
}

class FHQTreap
{
    int root = nil;
    void up(int i) { sz[i] = sz[lch[i]] + 1 + sz[rch[i]]; }
    void split(int l, int r, int i, int k) {
        if (i == nil) {
            rch[l] = lch[r] = nil;
            return;
        }
        if (key[i] <= k) {
            rch[l] = i;
            split(i, r, rch[i], k);
        } else {
            lch[r] = i;
            split(l, i, lch[i], k);
        }
        up(i);
    }
    ii split(int n, int k) {
        split(0, 0, n, k);
        ii ret = { rch[0], lch[0] };
        lch[0] = rch[0] = nil;
        return ret;
    }
    int merge(int l, int r) {
        if (l == nil or r == nil) return l + r;
        if (prio[l] > prio[r]) {
            rch[l] = merge(rch[l], r);
            up(l);
            return l;
        } else {
            lch[r] = merge(l, lch[r]);
            up(r);
            return r;
        }
    }
    
    int find_by_order(int n, int k) {
        if (k < sz[lch[n]]) return find_by_order(lch[n], k);
        if (k <= sz[lch[n]]) return key[n];
        return find_by_order(rch[n], k - sz[lch[n]] - 1);
    }
    int order_of_key(int n, int x) {
        if (n == nil) return 0;
        if (x <= key[n]) return order_of_key(lch[n], x);
        if (key[n] < x) return sz[lch[n]] + 1 + order_of_key(rch[n], x);
    }
    
    int upper_bound(int n, int x) {
        if (n == nil) return 1e9;
        if (x < key[n]) return min(key[n], upper_bound(lch[n], x));
        if (key[n] <= x) return upper_bound(rch[n], x);
    }
    int pre_lower_bound(int n, int x) {
        if (n == nil) return -1e9;
        if (x <= key[n]) return pre_lower_bound(lch[n], x);
        if (key[n] < x) return max(key[n], pre_lower_bound(rch[n], x));
    }
    
public:
    void insert(int x) {
        auto [l, r] = split(root, x);
        root = merge(merge(l, make_node(x)), r);
    }
    void erase(int x) {
        auto [lm, r] = split(root, x);
        auto [l, m] = split(lm, x - 1);
        m = merge(lch[m], rch[m]);
        root = merge(merge(l, m), r);
    }
    int find_by_order(int k) { return find_by_order(root, k); }
    int order_of_key(int x) { return order_of_key(root, x); }
    int upper_bound(int x) { return upper_bound(root, x); }
    int pre_lower_bound(int x) { return pre_lower_bound(root, x); }
};