class SegmentTree
{
	#define SETM int m = (l + r) / 2;
	#define IN_RANGE (i <= l and r <= j)
	#define LEFT lch[p], l, m
	#define RIGHT rch[p], m+1, r
	void pull(int p) { info[p] = info[lch[p]] + info[rch[p]]; }
public:
	int make_tree(int i, int l=1, int r=n+1) {
		if (l == r) { info[c1] = 1; return c1++; }
		SETM
		int p = c1++;
		if (i <= m) lch[p] = make_tree(i, l, m);
		if (i > m) rch[p] = make_tree(i, m + 1, r);
		pull(p);
		return p;
	}
	int merge(int p1, int p2) {
		if (p1 == nil or p2 == nil) return p1 + p2;
		info[p1] += info[p2];
		lch[p1] = merge(lch[p1], lch[p2]);
		rch[p1] = merge(rch[p1], rch[p2]);
		return p1;
	}
	int query(int i, int j, int p, int l=1, int r=n+1) {
		if IN_RANGE return info[p];
		SETM
		int ans = 0;
		if (i <= m) ans += query(i, j, LEFT);
		if (j > m) ans += query(i, j, RIGHT);
		return ans;
	}
};

int t[MAXN];
int ans[MAXN];
void dfs(int v) {
	for (int u : T[v]) {
		dfs(u);
		t[v] = st.merge(t[v], t[u]);
	}
	ans[v] = st.query(p[v] + 1, n + 1, t[v]);
}