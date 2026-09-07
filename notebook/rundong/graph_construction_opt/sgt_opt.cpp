class SegmentTree {
	vi vtx;
	bool is_intree;
	#define LEFT l, m, 2*p 
	#define RIGHT m+1, r, 2*p+1 
	#define SETM int m = (l + r) / 2;
	#define IN_RANGE (i <= l and r <= j)
	#define PULL pull(p);
	void pull(int p) {
		if (is_intree)
			forn(i, 2) add_edge(vtx[p], vtx[2*p+i]);
		else
			forn(i, 2) add_edge(vtx[2*p+i], vtx[p]);
	}
	void build(int l, int r, int p) {
		if (l == r) { vtx[p] = l; return; }
		vtx[p] = ++nV;
		SETM build(LEFT); build(RIGHT); PULL
	}
public:
	SegmentTree() = default;
	SegmentTree(bool in) : vtx(4 << __lg(n)), is_intree(in) {
		build(1, n, 1);
	}
	void get_vertices(int i, int j, vi* out, int l=1, int r=n, int p=1) {
		if IN_RANGE { out->push_back(vtx[p]); return; }
		SETM
		if (i <= m) get_vertices(i, j, out, LEFT);
		if (j > m) get_vertices(i, j, out, RIGHT);
	}
} inT;