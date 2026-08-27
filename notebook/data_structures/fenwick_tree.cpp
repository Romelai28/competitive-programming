// O(log(n)) por query o update.
// Interpretacion 1: Point update, range query.
// Interpretacion 2: Range update, point query.

struct FenwickTree {
	int n; vector<ll> bit;  // binary indexed tree (indexado desde 0)
	
	FenwickTree(int N) : n(N), bit(N) {}
	
	// 1: Devuelve la suma [0, r].
	// 2: Devuelve A[r]. (Point query)
	ll get_sum(int r) {
		ll ret = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1){
			ret += bit[r];
		}
		return ret;
	}
	
	// 1: Hace A[idx] += delta.
	// 2: Hace A[i] += delta para i en [idx, ... INF] 
	void add(int idx, ll delta) {
		for (; idx < n; idx = idx | (idx + 1)){
			bit[idx] += delta;
		}
	}
	
	// Exclusivo 1: Devuelve la suma [l, r].
	ll get_sum(int l, int r) {
		return get_sum(r) - get_sum(l - 1);
	}
	
	// Exclusivo 2: Hace A[i] += val para todo i en [l, r].
	void range_add(int l, int r, ll val) {
		add(l, val);
		add(r + 1, -val);
	}
};
