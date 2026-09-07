const int N = 1e7;
ll info[N];
int lch[N], rch[N];
ll tag[N];
int c1 = 2;
int root_of_version[N];
int c2 = 1;

class PersistentSegmentTree
{
	int n;
	
	int clone(int p) {
		int i = c1++;
		info[i] = info[p];
		lch[i] = lch[p];
		rch[i] = rch[p];
		tag[i] = tag[p];
		return i;
	}
	
	#define SETM int m = (l + r) / 2;
	#define CLONE int \
		t = clone(lch[p]); lch[p] = t; \
		t = clone(rch[p]); rch[p] = t;
	#define LEFT l, m, lch[p]
	#define RIGHT m+1, r, rch[p]
	#define PULL pull(l, r, p);
	#define PUSH push(l, r, p);
	#define IN_RANGE (i <= l and r <= j)
	
	void pull(int l, int r, int p) {
		info[p] = info[lch[p]] + info[rch[p]];
	}
	
	void build(const vi& a, int l, int r, int p) {
		if (l == r) { info[p] = a[l]; return; }
		SETM CLONE 
		build(a, LEFT);
		build(a, RIGHT);
		PULL 
	}
	
	void add_lazy(ll x, int l, int r, int p) {
		tag[p] += x;
		info[p] += (r - l + 1) * x;
	}
	
	void push(int l, int r, int p) {
		if (tag[p]) {
			SETM CLONE
			add_lazy(tag[p], LEFT);
			add_lazy(tag[p], RIGHT);
			tag[p] = 0;
		}
	}
	
	void add(int i, int j, ll x, int l, int r, int p) {
		if IN_RANGE { add_lazy(x, l, r, p); return; }
		if (not tag[p]) { CLONE }
		SETM PUSH 
		if (i <= m) add(i, j, x, LEFT);
		if (j > m) add(i, j, x, RIGHT);
		PULL 
	}
	
	ll query(int i, int j, int l, int r, int p) {
		if IN_RANGE return info[p];
		SETM PUSH
		ll ans = 0;
		if (i <= m) ans += query(i, j, LEFT);
		if (j > m) ans += query(i, j, RIGHT);
		return ans;
	}
	
public:
	PersistentSegmentTree(const vi& a) : n(a.size() - 1) {
		root_of_version[0] = 1;
		build(a, 1, n, 1);
	}
	
	int add(int v, int i, int j, ll x) {
		int p = clone(root_of_version[v]);
		add(i, j, x, 1, n, p);
		return p;
	}
	
	ll query(int v, int i, int j) {
		int p = root_of_version[v];
		ll ans = query(i, j, 1, n, p);
		return ans;
	}
};