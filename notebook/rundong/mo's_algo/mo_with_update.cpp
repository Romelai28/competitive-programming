const int MAXN = 2e5 + 1;
int n, q;
int a[MAXN];
short op[MAXN];
int L[MAXN], R[MAXN];
int * const I = L;
int * const V = R;

int block_size;
short bi[MAXN];

int qQ = 0, qC = 0, ts = 0;
int qry[MAXN];
int change[MAXN];
int tim[MAXN];
int ans[MAXN];

int freq[MAXN];
struct Window {
	int l = 1, r = 0, iT = 0;
	int ans = 0;
	void add(int x) {
		if (freq[x] == 1) ans--;
		freq[x]++;
		if (freq[x] == 1) ans++;
	}
	void del(int x) {
		if (freq[x] == 1) ans--;
		freq[x]--;
		if (freq[x] == 1) ans++;
	}
	void update(int qi) {
		if (l <= I[qi] and I[qi] <= r)
			del(a[I[qi]]),
			add(V[qi]);
		swap(a[I[qi]], V[qi]);
	}
	void forward() { iT++; update(change[iT]); }
	void back() { update(change[iT]); iT--; }
	int query(int i, int j, int t) {
		while (i < l) add(a[--l]);
		while (j > r) add(a[++r]);
		while (i > l) del(a[l++]);
		while (j < r) del(a[r--]);
		while (iT + 1 <= qC and tim[change[iT + 1]] <= t) forward();
		while (iT > 0 and tim[change[iT]] > t) back();
		return ans;
	}
} w;

// main
	for1(i, n) cin >> a[i];
	for1(i, q) cin >> op[i] >> L[i] >> R[i];
	for1(i, q)
	if (op[i] == 1) I[i]++;
	else L[i]++, R[i]++;
	block_size = pow(n, 2.0 / 3);
	for (int i = 1, b = 1; i <= n; i += block_size, b++) {
		int br = min(i + block_size - 1, n);
		for (int j = i; j <= br; ++j) bi[j] = b;
	}
	for1(i, q)
	if (op[i] == 1)
		change[++qC] = i, tim[i] = ++ts;
	else
		qry[++qQ] = i, tim[i] = ts;
	sort(qry+1, qry+1 + qQ, [](int i, int j) {
		if (bi[L[i]] == bi[L[j]]) {
			if (bi[R[i]] == bi[R[j]]) {
				// if (bi[R[i]] % 2)
					return tim[i] < tim[j];
				// return tim[i] > tim[j];
			}
			return bi[R[i]] < bi[R[j]];
		}
		return bi[L[i]] < bi[L[j]];
	});
	for1(i, qQ) {
		int qi = qry[i];
		ans[qi] = w.query(L[qi], R[qi], tim[qi]);
	}