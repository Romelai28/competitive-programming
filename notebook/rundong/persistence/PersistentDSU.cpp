const int nil = 0;
class PersistentArray
{
    int n;
    vi info;
    vi lch, rch;
    vi root_of_version;
    int clone(int p) {
        int i = info.size();
        info.push_back(info[p]);
        lch.push_back(lch[p]);
        rch.push_back(rch[p]);
        return i;
    }
    #define SETM int tt, m = (l + r) / 2;
    #define LEFT l, m, lch[p]
    #define RIGHT m+1, r, rch[p]
    #define LEFT_CLONE l, m, (tt = clone(lch[p]), lch[p] = tt)
    #define RIGHT_CLONE m+1, r, (tt = clone(rch[p]), rch[p] = tt)
    void build(const vi& v, int l, int r, int p) {
        if (l == r) { info[p] = v[l]; return; }
        SETM
        build(v, LEFT_CLONE);
        build(v, RIGHT_CLONE);
    }
    void set(int i, int x, int l, int r, int p) {
        if (l == r) { info[p] = x; return; }
        SETM
        if (i <= m) set(i, x, LEFT_CLONE);
        if (i > m) set(i, x, RIGHT_CLONE);
    }
    int get(int i, int l, int r, int p) {
        if (l == r) return info[p];
        SETM
        if (i <= m) return get(i, LEFT);
        if (i > m) return get(i, RIGHT);
    }
public:
    PersistentArray() = default;
    PersistentArray(const vi& v) : n(v.size() - 1), info(2, 0),
        lch(2, nil), rch(2, nil), root_of_version(1, 1) { build(v, 1, n, 1); }
    void set(int v, int i, int x) {
        int p = clone(root_of_version[v]);
        set(i, x, 1, n, p);
        root_of_version.push_back(p);
    }
    int get(int v, int i) {
        int p = root_of_version[v];
        return get(i, 1, n, p);
    }
    int last_version() { return root_of_version.size() - 1; }
};

class PersistentDSU
{
    PersistentArray p, s;
    vi pvers = { 0 }, svers = { 0 };
    int find(int i) {
        int v = pvers.back();
        int pa = p.get(v, i);
        return pa == i ? i : find(pa);
    }
public:
    PersistentDSU(int n) {
        vi v(n + 1, 1);
        s = PersistentArray(v);
        for1(i, n) v[i] = i;
        p = PersistentArray(v);
    }
    bool in_same_set(int i, int j) {
        bool ans = find(i) == find(j);
        pvers.push_back(pvers.back());
        svers.push_back(svers.back());
        return ans;
    }
    bool unite(int i, int j) {
        int vp = pvers.back();
        int vs = svers.back();
        i = find(i); j = find(j);
        if (i == j) {
            pvers.push_back(vp);
            svers.push_back(vs);
            return false;
        }
        int si = s.get(vs, i), sj = s.get(vs, j);
        if (si > sj) swap(i, j), swap(si, sj);
        p.set(vp, i, j);
        s.set(vs, j, si + sj);
        pvers.push_back(p.last_version());
        svers.push_back(s.last_version());
        return true;
    }
    void travel_to(int k) {
        pvers.push_back(pvers[k]);
        svers.push_back(svers[k]);
    }
};