// Segment tree para range update y point query

struct SegmentTreeLazy{
	int n;
	vl A, B;
	ll elemNeutro;

	SegmentTreeLazy(int N, vl &a, ll neutro) : n(N), A(a), elemNeutro(neutro){
		B.resize(4*n, elemNeutro);
		build(1, 0, n-1);
	}

	void build(int v, int tl, int tr){ // Vertice actual y rango [tl, tr] que indica este vertice
		if (tl == tr) B[v] = A[tl]; // Cuando llego a una hoja, el valor es el mismo elemento
		else {
			int tm = (tl + tr)/2;
			build(2*v, tl, tm);
			build(2*v+1, tm+1, tr); 
		}
	}

	ll query(int v, int tl, int tr, int pos){
		if (tl == tr) return B[v];
		int tm = (tl+tr)/2;
		if (pos <= tm) return B[v] + query(2*v, tl, tm, pos);
		return B[v] + query(2*v+1, tm+1, tr, pos);
	}

	void update(int v, int tl, int tr, int l, int r, ll add){
		if (l > r) return ;
		if (l == tl && r == tr) B[v] += add;
		else {
			int tm = (tl + tr)/2;
			update(2*v, tl, tm, l, min(r, tm), add);
			update(2*v+1, tm+1, tr, max(l, tm+1), r , add);
		}
	}
};

