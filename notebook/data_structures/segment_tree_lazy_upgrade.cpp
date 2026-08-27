// Segment tree lazy generico (Info/Tag) para range update y range query

template <class Info, class Tag>
struct LazySegmentTree{
	int n;
	vector<Info> B;
	vector<Tag> L;

	LazySegmentTree(int N, vector<Info> &a) : n(N){
		B.resize(4*n, Info());
		L.assign(4*n, Tag());
		build(1, 0, n-1, a);
	}

	Info combine(Info x, Info y){ return x + y; }

	void build(int v, int tl, int tr, vector<Info> &a){
		if (tl == tr) B[v] = a[tl];
		else {
			int tm = (tl + tr)/2;
			build(2*v, tl, tm, a);
			build(2*v+1, tm+1, tr, a);
			B[v] = combine(B[2*v], B[2*v+1]);
		}
	}

	void apply(int v, int tl, int tr, const Tag &x){
		B[v].apply(x, tl, tr);
		L[v].apply(x);
	}

	void push_down(int v, int tl, int tr){
		int tm = (tl + tr)/2;
		apply(2*v, tl, tm, L[v]);
		apply(2*v+1, tm+1, tr, L[v]);
		L[v] = Tag();
	}

	// query(1, 0, n-1, l, r)
	Info query(int v, int tl, int tr, int l, int r){
		if (l > r) return Info();
		if (l == tl && r == tr) return B[v];
		push_down(v, tl, tr);
		int tm = (tl + tr)/2;
		return combine(query(2*v, tl, tm, l, min(r, tm)),
						query(2*v+1, tm+1, tr, max(l, tm+1), r));
	}

	// update(1, 0, n-1, l, r, x)
	void update(int v, int tl, int tr, int l, int r, const Tag &x){
		if (l > r) return;
		if (l == tl && r == tr){ apply(v, tl, tr, x); return; }
		push_down(v, tl, tr);
		int tm = (tl + tr)/2;
		update(2*v, tl, tm, l, min(r, tm), x);
		update(2*v+1, tm+1, tr, max(l, tm+1), r, x);
		B[v] = combine(B[2*v], B[2*v+1]);
	}
};

enum QueryType { ADD, SET, NONE };

const int NEUTRO_TAG = 0;
struct Tag {
	QueryType type = NONE; // NONE = elemento neutro: apply() no hace nada
	ll val = NEUTRO_TAG;
	void apply(const Tag &t) {
		if (t.type == ADD) {
			val += t.val;
			if (type != SET) type = ADD; 
		} else if (t.type == SET) {
			type = SET;
			val = t.val;
		}
	}
};

const int NEUTRO_INFO = 0;
struct Info {
	ll sum = NEUTRO_INFO; // sum = 0 es neutro para combine (operator+) y para apply con Tag neutro
	void apply(const Tag &t, int l, int r) {
		if (t.type == SET) {
			sum = t.val * (r - l + 1);
		} else if (t.type == ADD) {
			sum += t.val * (r - l + 1);
		}
	}
};

/** @return result of joining nodes a and b together */
Info operator+(const Info &a, const Info &b) { return {a.sum + b.sum}; }

// Tag Q = Tag{SET, x}; 
// Tag Q = Tag{ADD, X};
// T.update(1, 0, n-1, l, r, Q);