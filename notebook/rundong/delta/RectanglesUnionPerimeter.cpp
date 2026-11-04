class SegmentTree {
    const vi coords;
    int rank(int x) { return lower_bound(all(coords), x) - coords.begin(); }
    int n;
    vi cover;
    vi cnt;
    #define LEFT l, m, 2*p 
    #define RIGHT m+1, r, 2*p+1 
    #define SETM int m = l + (r - l) / 2;
    #define IN_RANGE (i <= l and r <= j)
    void push_up(int l, int r, int p) {
        if (cnt[p]) cover[p] = coords[r] - coords[l - 1];
        else if (l == r) cover[p] = 0;
        else cover[p] = cover[2*p] + cover[2*p+1];
    }
    #define UP push_up(l, r, p);
    void add(int i, int j, int x, int l, int r, int p) {
        if IN_RANGE { cnt[p] += x; UP } else {
            SETM
            if (i <= m) add(i, j, x, LEFT);
            if (j > m) add(i, j, x, RIGHT);
            UP
        }
    }
public:
    SegmentTree(const vi& coords) : coords(coords),
        n(coords.size() - 1), cover(4 * n, 0), cnt(4 * n, 0) {}
    void inc(int i, int j) { add(rank(i), rank(j), 1, 1, n, 1); }
    void dec(int i, int j) { add(rank(i), rank(j), -1, 1, n, 1); }
    int query() { return cover[1]; }
};

void compress(vi& v) {
    sort(all(v));
    v.erase(unique(all(v)), v.end());
}
vi coords;

const int MAXN = 5e3 + 10;
int n;
int X1[MAXN], Y1[MAXN], X2[MAXN], Y2[MAXN];
struct Event {
    int time;
    int l, r;
    bool is_start;
    bool operator<(const Event& b) const {
        if (time == b.time) return is_start > b.is_start;
        return time < b.time;
    }
};
vector<Event> evs;

ll solve() {
    coords = { (int)-1e5 };
    forn(i, n) for (int x : { Y1[i], Y2[i], Y1[i]-1, Y2[i]-1 })
        coords.push_back(x);
    compress(coords);
    forn(i, n)
        evs.push_back({ X1[i], Y1[i], Y2[i]-1, true }),
        evs.push_back({ X2[i], Y1[i], Y2[i]-1, false });
    sort(all(evs));
    
    ll ans = 0;
    SegmentTree st(coords);
    for (auto& ev : evs)
    {
        auto [time, l, r, is_start] = ev;
        int prev = st.query();
        if (is_start) {
            st.inc(l, r);
            ans += st.query() - prev;
        } else {
            st.dec(l, r);
            ans += prev - st.query();
        }
    }
    
    coords = { (int)-1e5 };
    forn(i, n) for (int x : { X1[i], X2[i], X1[i]-1, X2[i]-1 })
        coords.push_back(x);
    compress(coords);
    
    evs.clear();
    forn(i, n)
        evs.push_back({ Y1[i], X1[i], X2[i]-1, true }),
        evs.push_back({ Y2[i], X1[i], X2[i]-1, false });
    sort(all(evs));
    
    SegmentTree st2(coords);
    for (auto& ev : evs)
    {
        auto [time, l, r, is_start] = ev;
        int prev = st2.query();
        if (is_start) {
            st2.inc(l, r);
            ans += st2.query() - prev;
        } else {
            st2.dec(l, r);
            ans += prev - st2.query();
        }
    }
    return ans;
}