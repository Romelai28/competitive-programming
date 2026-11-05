using Num = double; const Num eps = 1e-8;
int cmp(Num x, Num y) {
	if (x - y > eps) return 1;
	if (y - x > eps) return -1;
	return 0;
}
vector<pair<Num, Num>> linear = { {-1., -1.} };
Num eval(int s, int x) {
	auto [a, b] = linear[s];
	return a * x + b;
}
int info[N];
struct LiChaoTree {
	bool better(int s, int t, int m) {
		int c = cmp(eval(s, m), eval(t, m));
		if (c) return c == 1;
		return s < t;
	}
	void lazy(int s, int p, int l, int r) {
		if (not info[p]) { info[p] = s; return; }
		SETM 
		if (better(s, info[p], m)) swap(s, info[p]);
		int bl = cmp(eval(s, l), eval(info[p], l)),
			br = cmp(eval(s, r), eval(info[p], r));
		if (bl == 1 or not bl and s < info[p]) lazy(s, LEFT);
		if (br == 1 or not br and s < info[p]) lazy(s, RIGHT);
	}
public:
	void update(int i, int j, int s, int p=1, int l=0, int r=RB) {
		if IN_RANGE { lazy(s, p, l, r); return; }
		SETM
		if (i <= m) update(i, j, s, LEFT);
		if (j > m) update(i, j, s, RIGHT);
	}
	int query(int x, int p=1, int l=0, int r=RB) {
		if (l == r) return info[p];
		SETM
		int ans;
		if (x <= m) ans = query(x, LEFT);
		if (x > m) ans = query(x, RIGHT);
		if (better(info[p], ans, x)) ans = info[p];
		return ans;
	}
} sgt;