const int MAXN = 2e5 + 1, MAXV = 1e7, MAXE = 5e6;  // memory limit: 256mb
int n, a, b, p[MAXN], nV;
struct Graph {
	int head[MAXV], nxt[MAXE], to[MAXE];
	int edge_cnt = 0;
	void add_edge(int u, int v) {
		int e = ++edge_cnt;
		nxt[e] = head[u], to[e] = v, head[u] = e;
	}
	#define for_adj(u, v) for(int e = G.head[v], u, c; \
		u = G.to[e], e; e = G.nxt[e])
} G;
bool in_vertex[MAXV];
int forward[MAXV];
int lch[MAXV], rch[MAXV];
#define pa (lch)
#define backward (forward)
struct SegmentTree {
	bool in;
	int vtx[4 << __lg(MAXN)];
	#define LEFT 2*p, l, m 
	#define RIGHT 2*p+1, m+1, r 
	#define IN_RANGE (i <= l and r <= j)
	#define SETM int m = (l + r) / 2;
	#define PULL pull(p);
	void pull(int p) {
		if (in) {
			lch[vtx[p]] = vtx[2*p];
			rch[vtx[p]] = vtx[2*p+1];
		} else {
			if (vtx[2*p] and not pa[vtx[2*p]]) pa[vtx[2*p]] = vtx[p];
			if (vtx[2*p+1] and not pa[vtx[2*p+1]]) pa[vtx[2*p+1]] = vtx[p];
		}
	}
	void get_vertices(int i, int j, vi& out, int p, int l, int r) {
		if IN_RANGE { if (vtx[p]) out.push_back(vtx[p]); return; }
		SETM
		if (i <= m) get_vertices(i, j, out, LEFT);
		if (j > m) get_vertices(i, j, out, RIGHT);
	}
public:
	void add_vertex(int v, int p=1, int l=1, int r=n) {
		if (l == r) { vtx[p] = v; return; }
		if (in) {
			int u = ++nV;
			in_vertex[u] = true;
			forward[u] = vtx[p];
			vtx[p] = u;
		} else {
			int u = ++nV;
			in_vertex[u] = false;
			if (vtx[p]) backward[vtx[p]] = u;
			vtx[p] = u;
		}
		SETM
		if (v <= m) add_vertex(v, LEFT);
		if (v > m) add_vertex(v, RIGHT);
		PULL 
	}
	vi& get_vertices(int i, int j, vi& out) {
		i = max(i, 1); j = min(j, n);
		if (i <= j) get_vertices(i, j, out, 1, 1, n);
		return out;
	}
	void clear(int p=1, int l=1, int r=n) {
		vtx[p] = 0;
		if (l < r) { SETM clear(LEFT), clear(RIGHT); }
	}
} out_sgt{false}, in_sgt{true};
int idx[MAXN];
vi vs;
deque<ii> que;
const int oo = 1e9;
int D[MAXV];
void check0(int d, int u) {
	if (d < D[u]) D[u] = d, que.push_front({ d, u });
}
int bfs01() {
	for1(v, nV) D[v] = oo;
	D[a] = 0;
	que.clear();
	que.push_back({ D[a], a });
	while (not que.empty()) {
		auto [d, v] = que.front(); que.pop_front();
		if (d > D[v]) continue;
		int u;
		if (1 <= v and v <= n) {
			for_adj(u, v) if (d + 1 < D[u]) {
				D[u] = d + 1;
				que.push_back({ D[u], u });
			}
			check0(d, pa[v]);
		} else if (in_vertex[v]) {
			check0(d, forward[v]);
			check0(d, lch[v]);
			check0(d, rch[v]);
		} else {
			check0(d, backward[v]);
			check0(d, pa[v]);
			for_adj(u, v) if (d + 1 < D[u]) {
				D[u] = d + 1;
				que.push_back({ D[u], u });
			}
		}
	}
	return D[b];
}
// main
	cin >> n >> a >> b;
	for1(v, n) cin >> p[v];
	nV = n;
	in_sgt.clear();
	out_sgt.clear();
	for1(v, n) idx[v] = v;
	sort(idx+1, idx+1 + n, [](int u, int v) { return p[u] > p[v]; });
	for1(i, n) {
		vs.clear();
		int v = idx[i];
		in_sgt.get_vertices(v - p[v], v + p[v], vs);
		for (int u : vs) G.add_edge(v, u);
		vs.clear();
		out_sgt.get_vertices(v - p[v], v + p[v], vs);
		for (int u : vs) G.add_edge(u, v);
		in_sgt.add_vertex(v);
		out_sgt.add_vertex(v);
	}
	cout << bfs01() << '\n';
