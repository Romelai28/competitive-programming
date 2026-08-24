using i16 = int16_t;
class SegmentTree {
    
    int n;
    vector<i16> info;
    
    #define SETM int m = (l + r) / 2;
    #define LEFT l, m, 2*p 
    #define RIGHT m+1, r, 2*p+1 
    #define IN_RANGE (i <= l and r <= j)
    #define PULL pull(p);
    
    void pull(int p) { info[p] = max(info[2*p], info[2*p+1]); }
    
    void update(int i, i16 x, int l, int r, int p) {
        if (l == r) { chmax(info[p], x); return; }
        SETM
        if (i <= m) update(i, x, LEFT);
        if (i > m) update(i, x, RIGHT);
        PULL 
    }
    
    i16 query(int i, int j, int l, int r, int p) {
        if IN_RANGE return info[p];
        SETM
        i16 ans = -2;
        if (i <= m) chmax(ans, query(i, j, LEFT));
        if (j > m) chmax(ans, query(i, j, RIGHT));
        return ans;
    }
    
public:
    SegmentTree(int n) : n(n), info(4*n, -1) {}
    void update(int i, i16 x) { update(i, x, 0, n, 1); }
    i16 query(int i, int j) { return query(i, j, 0, n, 1); }
};
class SegmentTree2D {
    
    int m;
    vector<SegmentTree> info;
    
    void update(int y, int x, i16 v, int l, int r, int p)
    {
        if (l == r) { info[p].update(x, v); return; }
        SETM
        if (y <= m) update(y, x, v, LEFT);
        if (y > m) update(y, x, v, RIGHT);
        info[p].update(x, v);
    }
    
    i16 query(int yi, int yj, int xi, int xj, int l, int r, int p) {
        if (yi <= l and r <= yj) return info[p].query(xi, xj);
        SETM
        i16 ans = -2;
        if (yi <= m) chmax(ans, query(yi, yj, xi, xj, LEFT));
        if (yj > m) chmax(ans, query(yi, yj, xi, xj, RIGHT));
        return ans;
    }

public:
    SegmentTree2D(int m, int n) : m(m),
        info(4*m, SegmentTree(n)) {}
    void update(int y, int x, i16 v) { update(y, x, v, 0, m, 1); }
    i16 query(int yi, int yj, int xi, int xj) {
        return query(yi, yj, xi, xj, 0, m, 1);
    }
};