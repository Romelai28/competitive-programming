struct DisjointSet{
	vi parent, rnk;
	int comps;

	DisjointSet(int n) : parent(n), rnk(n, 0), comps(n){
		iota(all(parent), 0);
	}

	int findSet(int x){
		if(parent[x]!=x) {parent[x] = findSet(parent[x]);}
		return parent[x];
	}

	void unionSet(int x, int y){
		x = findSet(x); y = findSet(y);
		if (x != y){
			if (rnk[x] < rnk[y]) {parent[x] = y;}
			else if (rnk[x] > rnk[y]) {parent[y] = x;}
			else {parent[y] = x; rnk[x]++;}
			comps--;
		}
	}

	bool same(int x, int y) {return findSet(x) == findSet(y);}
};
