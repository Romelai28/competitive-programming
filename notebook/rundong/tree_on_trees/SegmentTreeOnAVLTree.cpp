const int oo = -((1 << 31) + 1);
const int nil = 0;
const int N = 2e7;
int lch[N], rch[N];
int height[N], sz[N];
int key[N], cnt[N];
int c1 = 1;
class AVLTree {
    int root = nil;
    void up(int n) {
        height[n] = 1 + max(height[lch[n]], height[rch[n]]);
        sz[n] = cnt[n] + sz[lch[n]] + sz[rch[n]];
    }
    int left_rotate(int n) {
        int r = rch[n];
        rch[n] = lch[r];
        lch[r] = n;
        up(n);
        up(r);
        return r;
    }
    int right_rotate(int n) {
        int l = lch[n];
        lch[n] = rch[l];
        rch[l] = n;
        up(n);
        up(l);
        return l;
    }
    int maintain(int n) {
        int lh = height[lch[n]],
            rh = height[rch[n]];
        if (lh > rh + 1) {
            if (height[lch[lch[n]]] >= height[rch[lch[n]]])
                n = right_rotate(n);
            else
                lch[n] = left_rotate(lch[n]),
                n = right_rotate(n);
        } else if (rh > lh + 1) {
            if (height[rch[rch[n]]] >= height[lch[rch[n]]])
                n = left_rotate(n);
            else
                rch[n] = right_rotate(rch[n]),
                n = left_rotate(n);
        }
        return n;
    }
    
    int make_node(int v) {
        int n = c1++;
        height[n] = 1; sz[n] = 1;
        key[n] = v; cnt[n] = 1;
        return n;
    }
    int insert(int n, int v) {
        if (n == nil) return make_node(v);
        if (v < key[n]) lch[n] = insert(lch[n], v);
        else if (v == key[n]) cnt[n]++;
        else rch[n] = insert(rch[n], v);
        up(n);
        return maintain(n);
    }
    pair<int, int> get_leftmost(int n) {
        if (lch[n] == nil) return { rch[n], n };
        
        auto [ i, leftmost ] = get_leftmost(lch[n]);
        lch[n] = i;
        up(n);
        return { maintain(n), leftmost };
    }
    int erase(int n, int v) {
        if (n == nil) return nil;
        
        if (v < key[n]) lch[n] = erase(lch[n], v);
        else if (v > key[n]) rch[n] = erase(rch[n], v);
        else if (cnt[n] > 1) cnt[n]--;
        else
        {
            if (lch[n] == nil and rch[n] == nil) return 0;
            
            if (lch[n] == nil or rch[n] == nil)
                n = lch[n] + rch[n];
            else
            {
                auto [ i, leftmost ] = get_leftmost(rch[n]);
                int l = lch[n];
                lch[leftmost] = l;
                rch[leftmost] = i;
                n = leftmost;
            }
        }
        
        up(n);
        return maintain(n);
    }
    
    int count(int n, int v) {
        if (n == nil) return 0;
        if (v < key[n]) return count(lch[n], v);
        if (v == key[n]) return cnt[n];
        if (v > key[n]) return count(rch[n], v);
    }
    
    int order_of_key(int n, int v) {
        if (n == nil) return 0;
        if (v <= key[n]) return order_of_key(lch[n], v);
        if (v > key[n]) return sz[lch[n]] + cnt[n] + order_of_key(rch[n], v);
    }
    
    int find_by_order(int n, int k) {
        if (n == nil) return nil;
        if (k < sz[lch[n]]) return find_by_order(lch[n], k);
        if (k < sz[lch[n]] + cnt[n]) return n;
        return find_by_order(rch[n], k - sz[lch[n]] - cnt[n]);
    }
    
    int nmax(int n1, int n2) {
        if (n1 == nil or n2 == nil) return n1 + n2;
        return key[n1] > key[n2] ? n1 : n2;
    }
    int prev_lower_bound(int n, int v) {
        if (n == nil) return nil;
        if (key[n] < v) return nmax(n, prev_lower_bound(rch[n], v));
        if (key[n] >= v) return prev_lower_bound(lch[n], v);
    }
    
    int nmin(int n1, int n2) {
        if (n1 == nil or n2 == nil) return n1 + n2;
        return key[n1] < key[n2] ? n1 : n2;
    }
    int upper_bound(int n, int v) {
        if (n == nil) return nil;
        if (key[n] <= v) return upper_bound(rch[n], v);
        if (key[n] > v) return nmin(n, upper_bound(lch[n], v));
    }
    
public:
    
    void insert(int v) { root = insert(root, v); }
    void erase(int v) { root = erase(root, v); }
    int count(int v) { return count(root, v); }
    int order_of_key(int v) { return order_of_key(root, v); }
    int find_by_order(int k) { return find_by_order(root, k); }
    int prev_lower_bound(int v) { return prev_lower_bound(root, v); }
    int upper_bound(int v) { return upper_bound(root, v); }
    int predecessor(int v) {
        int n = prev_lower_bound(v);
        if (n == nil) return -oo;
        else return key[n];
    }
    int successor(int v) {
        int n = upper_bound(v);
        if (n == nil) return oo;
        else return key[n];
    }
};

const int MAXN = 2e5 + 1;
int n, q;
int a[MAXN];

class SegmentTree {
    int n;
    vector<AVLTree> info;
    #define SETM int m = l + (r - l) / 2;
    #define LEFT l, m, 2*p 
    #define RIGHT m+1, r, 2*p+1 
    #define IN_RANGE (i <= l and r <= j)
    void set(int i, int v, int l, int r, int p) {
        if (l < r) { 
            SETM
            if (i <= m) set(i, v, LEFT);
            if (i > m) set(i, v, RIGHT);
        }
        info[p].insert(v);
    }
    void erase(int i, int l, int r, int p) {
        if (l < r) {
            SETM
            if (i <= m) erase(i, LEFT);
            if (i > m) erase(i, RIGHT);
        }
        info[p].erase(a[i]);
    }
    int order_of_key(int i, int j, int v, int l, int r, int p) {
        if IN_RANGE return info[p].order_of_key(v);
        SETM
        int ans = 0;
        if (i <= m) ans += order_of_key(i, j, v, LEFT);
        if (j > m) ans += order_of_key(i, j, v, RIGHT);
        return ans;
    }
    bool f(int v, int i, int j, int k) {
        int cnt = order_of_key(i, j, v, 1, n, 1);
        return k <= cnt;
    }
    int bin_search(int l, int r, int i, int j, int k) {
        if (l == r) return l;
        SETM
        if (f(m, i, j, k)) return bin_search(l, m, i, j, k);
        else return bin_search(m + 1, r, i, j, k);
    }
    int predecessor(int i, int j, int v, int l, int r, int p) {
        if IN_RANGE return info[p].predecessor(v);
        SETM
        int ans = -oo;
        if (i <= m) ans = max(ans, predecessor(i, j, v, LEFT));
        if (j > m) ans = max(ans, predecessor(i, j, v, RIGHT));
        return ans;
    }
    int successor(int i, int j, int v, int l, int r, int p) {
        if IN_RANGE return info[p].successor(v);
        SETM
        int ans = oo;
        if (i <= m) ans = min(ans, successor(i, j, v, LEFT));
        if (j > m) ans = min(ans, successor(i, j, v, RIGHT));
        return ans;
    }
public:
    SegmentTree(int n) : n(n), info(4*n) {}
    void set(int i, int v) { set(i, v, 1, n, 1); }
    void erase(int i) { erase(i, 1, n, 1); }
    int order_of_key(int i, int j, int v) { return order_of_key(i, j, v, 1, n, 1); }
    int find_by_order(int i, int j, int k) {
        return bin_search(0, 1e8+1, i, j, k + 1) - 1;
    }
    int predecessor(int i, int j, int v) { return predecessor(i, j, v, 1, n, 1); }
    int successor(int i, int j, int v) { return successor(i, j, v, 1, n, 1); }
};  // find_by_order O(log^3)