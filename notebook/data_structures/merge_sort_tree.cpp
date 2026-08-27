template <typename T>
using ordered_multiset = tree<
	pair<T, int>,
	null_type,
	less<pair<T, int>>, // NOT less_equal
	rb_tree_tag,
	tree_order_statistics_node_update
>;

// Segment tree donde guardo los elementos de cada rango en los vertice de forma ordenada
// Este segment tree te permite responder en un rango cuantos elementos k cumplen tq: x <= k <= y

struct SegmentTree{
	int n;
	vl A;
	ll elemNeutro;

	vector<ordered_multiset<ll>> B;

	SegmentTree(int N, vl &a, ll neutro) : n(N), A(a), elemNeutro(neutro){
		B.resize(4*n);
		build(1, 0, n-1); // O(n * log(n)^2)
	}

	ll f(int v, ll x, ll y){
		// # elementos < y+1 y # elementos < x
		ll res = B[v].order_of_key({y+1, -1}) - B[v].order_of_key({x, -1});
		return res;
	}

	void build(int v, int tl, int tr){ // Vertice actual y rango [tl, tr] que indica este vertice
		forsn(i, tl, tr+1) B[v].insert({A[i], i});
		if (tl < tr) {
			int tm = (tl + tr)/2;
			build(2*v, tl, tm);
			build(2*v+1, tm+1, tr); 
		}
	}

	// query(1, 0, n-1, l, r)
	ll query(int v, int tl, int tr, int l, int r, ll x, ll y){
		if (l > r) return elemNeutro; 
		if (l == tl && r == tr) return f(v, x, y); // Respondo la query en este rango
		int tm = (tl+tr)/2;
		return query(2*v, tl, tm, l, min(r, tm), x, y) + query(2*v+1, tm+1, tr, max(l, tm+1), r, x, y);
	}

	void update(int v, int tl, int tr, int pos, ll new_val){
		B[v].erase({A[pos], pos});
		B[v].insert({new_val, pos});
		if (tl < tr){
			int tm = (tl + tr)/2;
			if (pos <= tm) update(2*v, tl, tm, pos, new_val);
			else update(2*v+1, tm+1, tr, pos, new_val);
		}
		A[pos] = new_val;
	}
};
