const int N = 1e7;
int lch[N], rch[N];
int pa[N];
const int nil = 0;
int key[N];
int sz[N];
int c1 = 1;
const int oo = 1e9 + 10;

class SplayTree {
    int root = nil;
    int make_node(int x) {
        int i = c1++;
        key[i] = x; sz[i] = 1;
        return i;
    }
    void up(int i) { sz[i] = sz[lch[i]] + 1 + sz[rch[i]]; }
    bool lr(int i) { return i == rch[pa[i]]; }
    void rotate(int i) {
        int p = pa[i], g = pa[p];
        int ilr = lr(i), plr = lr(p);
        if (ilr == 1) {
            rch[p] = lch[i];
            lch[i] = p;
            if (rch[p]) pa[rch[p]] = p;
        } else {
            lch[p] = rch[i];
            rch[i] = p;
            if (lch[p]) pa[lch[p]] = p;
        }
        if (g) {
            if (plr == 1) rch[g] = i;
            else lch[g] = i;
        }
        
        pa[p] = i; pa[i] = g;
        up(p); up(i);
    }
    void splay(int i, int goal) {
        int p = pa[i], g = pa[p];
        while (p != goal) {
            if (g != goal) {
                if (lr(i) == lr(p)) rotate(p);
                else rotate(i);
            }
            rotate(i);
            p = pa[i]; g = pa[p];
        }
        
        if (goal == 0) root = i;
    }
    
    int find(int rank) {
        int i = root;
        while (i)
            if (sz[lch[i]] >= rank) i = lch[i];
            else if (sz[lch[i]] + 1 == rank) return i;
            else rank -= sz[lch[i]] + 1, i = rch[i];
        return 0;
    }
    
public:
    void insert(int x) {
        int j = make_node(x);
        if (root == nil) { root = j; return; }
        int i = root, p = nil, lr = 0;
        while (i) {
            p = i;
            if (x <= key[i]) i = lch[i], lr = 0;
            else i = rch[i], lr = 1;
        }
        
        pa[j] = p;
        if (lr) rch[p] = j;
        else lch[p] = j;
        
        splay(j, 0);
    }
    
    int rank(int x) {   // order_of_key but 1-indexed
        int i = root, last = root;
        int ans = 0;
        while (i) {
            last = i;
            if (x <= key[i]) i = lch[i];
            else ans += sz[lch[i]] + 1, i = rch[i];
        }
        
        splay(last, 0);
        return ans + 1;
    }
    
    void erase(int x) {
        int kth = rank(x);
        if (kth != rank(x + 1)) {
            int i = find(kth);
            splay(i, 0);
            if (lch[i] == 0) root = rch[i];
            else if (rch[i] == 0) root = lch[i];
            else {
                int j = find(kth + 1);
                splay(j, i);
                lch[j] = lch[i];
                pa[lch[j]] = j;
                up(j);
                root = j;
            }
            if (root) pa[root] = nil;
        }
    }
    
    int index(int k) {  // find_by_order but 1-indexed
        int i = find(k);
        splay(i, 0);
        return key[i];
    }
    
    int pre(int x) {
        int i = root, last = root;
        int ans = -oo;
        while (i) {
            last = i;
            if (x <= key[i]) i = lch[i];
            else ans = max(ans, key[i]), i = rch[i];
        }
        splay(last, 0);
        return ans;
    }
    int post(int x) {
        int i = root, last = root;
        int ans = oo;
        while (i) {
            last = i;
            if (key[i] <= x) i = rch[i];
            else ans = min(ans, key[i]), i = lch[i];
        }
        splay(last, 0);
        return ans;
    }
};