tint x[MAXN];
tint sorted[MAXN];
tint tag[MAXB];
short bi[MAXN];
int bl[MAXB], br[MAXB];

class Blocks
{
	int block_size;
	void inblock_add(int b, int l, int r, tint v) {
		forab(i, max(l, bl[b]), min(r, br[b])) x[i] += v;
		forab(i, bl[b], br[b]) sorted[i] = x[i];
		sort(sorted + bl[b], sorted + br[b] + 1);
	}
	void block_add(int b, tint v) { tag[b] += v; }
	int inblock_query(int b, int l, int r, tint v) {
		v -= tag[b];
		int ans = 0;
		forab(i, max(l, bl[b]), min(r, br[b])) ans += x[i] >= v;
		return ans;
	}
	int block_query(int b, tint v) {
		v -= tag[b];
		tint* p = upper_bound(sorted + bl[b], sorted + br[b] + 1, v - 1);
		return sorted + br[b] + 1 - p;
	}
public:
	Blocks(int n) {
		block_size = sqrt(n);
		for (int i = 0, b = 1; i <= n; i += block_size, b++) {
			bl[b] = i;
			br[b] = min(n, i + block_size - 1);
			for (int j = i; j <= br[b]; ++j) bi[j] = b;
		}
	}
	void add(int l, int r, tint v) {
		if (bi[l] == bi[r]) {
			inblock_add(bi[l], l, r, v);
			return;
		}
		inblock_add(bi[l], l, r, v);
		inblock_add(bi[r], l, r, v);
		for (int b = bi[l] + 1; b <= bi[r] - 1; ++b) block_add(b, v);
	}
	int query(int l, int r, tint v) {
		if (bi[l] == bi[r]) return inblock_query(bi[l], l, r, v);
		int ans = inblock_query(bi[l], l, r, v);
		ans += inblock_query(bi[r], l, r, v);
		for (int b = bi[l] + 1; b <= bi[r] - 1; ++b) ans +=
			block_query(b, v);
		return ans;
	}
};
int n, q;
int a[MAXN];
vector<ii> qry[MAXN];
vector<iii> events;
int ans[MAXN];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> q;
	for1(i, n) cin >> a[i];
	Blocks ds(q + 1);
	for1(i, q) {
		int op; cin >> op;
		if (op == 1) {
			int l, r, x; cin >> l >> r >> x;
			events.push_back({ l, { i, x } });
			events.push_back({ r + 1, { i, -x } });
			ans[i] = -1;
		}
		if (op == 2) {
			int p, y; cin >> p >> y;
			qry[p].push_back({ i, y });
		}
	}
	sort(ALL(events));
	int j = 0;
	for1(i, n)
	{
		ds.add(0, q, -a[i - 1]);
		ds.add(0, q, a[i]);
		while (j < events.size() and events[j].fst <= i) {
			auto [t, v] = events[j].snd;
			j++;
			ds.add(t, q, v);
		}
		for (auto [id, y] : qry[i]) {
			ans[id] = ds.query(0, id - 1, y);
		}
	}
	for1(i, q) if (ans[i] != -1) cout << ans[i] << '\n';
}