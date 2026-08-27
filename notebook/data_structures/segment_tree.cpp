// Segment tree basico para point update y range query de suma

struct SegmentTree{
	int n;
	vl A, B;
	ll elemNeutro;

	SegmentTree(int N, vl &a, ll neutro) : n(N), A(a), elemNeutro(neutro){
		B.resize(4*n, elemNeutro);
		build(1, 0, n-1);
	}

	ll combine(ll x, ll y){ return x + y;}
	ll make_data(ll x){ return x;}

	void build(int v, int tl, int tr){ // Vertice actual y rango [tl, tr] que indica este vertice
		if (tl == tr) B[v] = make_data(A[tl]); // Cuando llego a una hoja, el valor es el mismo elemento
		else {
			int tm = (tl + tr)/2;
			build(2*v, tl, tm);
			build(2*v+1, tm+1, tr); 
			B[v] = combine(B[2*v], B[2*v+1]);
		}
	}

	// query(1, 0, n-1, l, r)
	ll query(int v, int tl, int tr, int l, int r){
		if (l > r) return elemNeutro; 
		if (l == tl && r == tr) return B[v];
		int tm = (tl+tr)/2;
		return combine(query(2*v, tl, tm, l, min(r, tm)), query(2*v+1, tm+1, tr, max(l, tm+1), r));
	}

	void update(int v, int tl, int tr, int pos, ll new_val){
		if (tl == tr) B[v] = make_data(new_val);
		else {
			int tm = (tl + tr)/2;
			if (pos <= tm) update(2*v, tl, tm, pos, new_val);
			else update(2*v+1, tm+1, tr, pos, new_val);
			B[v] = combine(B[2*v], B[2*v+1]);
		}
	}
};

