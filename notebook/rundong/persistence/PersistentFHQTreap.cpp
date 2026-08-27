const int N = 5e7;
int lch[N], rch[N];
const int nil = 0;
int key[N];
int sz[N], prio[N];
int c1 = 1;

int root_of_version[N];
int c2 = 1;

int make_node(int x) {
	static mt19937 rng(random_device{}());
	static uniform_int_distribution<> dist(1, 1e9);
	int n = c1++;
	key[n] = x; sz[n] = 1; prio[n] = dist(rng);
	return n;
}
int clone(int n) {
	if (n == nil) return nil;
	int i = c1++;
	lch[i] = lch[n]; rch[i] = rch[n];
	key[i] = key[n];
	sz[i] = sz[n]; prio[i] = prio[n];
	return i;
}
#define CLONE(X) ((X) = clone(X))
class FHQTreap {
	void up(int n) { sz[n] = sz[lch[n]] + 1 + sz[rch[n]]; }
	void split(int l, int r, int n, int k) {
		if (n == nil) {
			rch[l] = lch[r] = 0;
			return;
		}
		if (key[n] <= k) {
			rch[l] = n;
			split(n, r, CLONE(rch[n]), k);
		} else {
			lch[r] = n;
			split(l, n, CLONE(lch[n]), k);
		}
		up(n);
	}
	ii split(int n, int k) {
		split(0, 0, clone(n), k);
		ii ret = { rch[0], lch[0] };
		rch[0] = lch[0] = nil;
		return ret;
	}
	int merge(int l, int r) {
		if (l == nil or r == nil) return l + r;
		if (prio[l] > prio[r]) {
			CLONE(l);
			rch[l] = merge(rch[l], r);
			up(l);
			return l;
		} else {
			CLONE(r);
			lch[r] = merge(l, lch[r]);
			up(r);
			return r;
		}
	}
	int _find_by_order(int n, int k) {
		assert(n != nil);
		if (k < sz[lch[n]]) return _find_by_order(lch[n], k);
		if (k < sz[lch[n]] + 1) return key[n];
		return _find_by_order(rch[n], k - sz[lch[n]] - 1);
	}
public:
	void insert(int v, int x) {
		int root = root_of_version[v];
		auto [l, r] = split(root, x);
		root = merge(merge(l, make_node(x)), r);
		root_of_version[c2++] = root;
	}
	void erase(int v, int x) {
		int root = root_of_version[v];
		auto [lm, r] = split(root, x);
		auto [l, m] = split(lm, x - 1);
		m = merge(lch[m], rch[m]);
		root = merge(merge(l, m), r);
		root_of_version[c2++] = root;
	}
	int order_of_key(int v, int x) {
		int root = root_of_version[c2++] = root_of_version[v];
		auto [l, r] = split(root, x - 1);
		return sz[l];
	}
	int find_by_order(int v, int x) {
		int root = root_of_version[c2++] = root_of_version[v];
		return _find_by_order(root, x);
	}
	int upper_bound(int v, int x) {
		int root = root_of_version[c2++] = root_of_version[v];
		auto [l, r] = split(root, x);
		while (lch[r] != nil) r = lch[r];
		return key[r];
	}
	int pre_lower_bound(int v, int x) {
		int root = root_of_version[c2++] = root_of_version[v];
		auto [l, r] = split(root, x - 1);
		while (rch[l] != nil) l = rch[l];
		return key[l];
	}
};