vi coords = { -1, 0, (int)1e9 + 5 };
vi cover;
vi cnt;
class SegmentTree {
	int rank(int x) { return lower_bound(all(coords), x) - coords.begin(); }
	int n;
	#define left l, m, 2*p 
	#define right m+1, r, 2*p+1 
	#define in_range (i <= l and r <= j)
	#define set_m int m = l + (r - l) / 2;
	void push_up(int l, int r, int p) {
		if (cnt[p]) cover[p] = coords[r] - coords[l - 1];
		else if (l == r) cover[p] = 0;
		else cover[p] = cover[2*p] + cover[2*p+1];
	}
	#define up push_up(l, r, p);
	void inc(int i, int j, int l, int r, int p) {
		if in_range { cnt[p]++; up; } else {
			set_m;
			if (i <= m) inc(i, j, left);
			if (j > m) inc(i, j, right);
			up;
		}
	}
	void dec(int i, int j, int l, int r, int p) {
		if in_range { cnt[p]--; up; } else {
			set_m;
			if (i <= m) dec(i, j, left);
			if (j > m) dec(i, j, right);
			up;
		}
	}
public:
	SegmentTree() : n(coords.size() - 1) {
		cover = vi(4 << __lg(n), 0);
		cnt = vi(4 << __lg(n), 0);
	}
	void inc(int i, int j) { inc(rank(i), rank(j), 1, n, 1); }
	void dec(int i, int j) { dec(rank(i), rank(j), 1, n, 1); }
	int query() { return cover[1]; }
};

const int MAXN = 1e5;
int n;
int x1[MAXN], y1[MAXN], x2[MAXN], y2[MAXN]; // conflictua con std
struct Event {
	int x;
	int y1, y2;
	bool start;
	bool operator<(const Event& b) const {
		if (x == b.x) return start > b.start;
		else return x < b.x;
	}
};
vector<Event> events;

int main() {
	cin >> n;
	forn(i, n) cin >> x1[i] >> y1[i] >> x2[i] >> y2[i], x2[i]--, y2[i]--;
	forn(i, n)
		events.push_back({ x1[i], y1[i], y2[i], true }),
		events.push_back({ x2[i], y1[i], y2[i], false });
	sort(all(events));
	forn(i, n)
		coords.push_back(y1[i]),
		coords.push_back(y2[i]),
		coords.push_back(y1[i] - 1),
		coords.push_back(y2[i] - 1);
	compress(coords);
	
	SegmentTree st;
	ll ans = 0;
	int prv = events[0].x - 1;
	
	forn(i, events.size()) {
		auto [x, y1, y2, start] = events[i];
		ll cover = st.query();
		ll xlen = x - 1 - prv;
		ans += cover * xlen;
		if (start) st.inc(y1, y2);
		while (i + 1 < events.size() and events[i+1].x == x
			and events[i+1].start)
			i++, st.inc(events[i].y1, events[i].y2);
		ans += st.query();
		if (not start) st.dec(y1, y2);
		while (i + 1 < events.size() and events[i+1].x == x
			and not events[i+1].start)
			i++, st.dec(events[i].y1, events[i].y2);

		prv = x;
	}
	cout << ans;
}