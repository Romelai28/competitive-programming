struct DisjointSetRollback{
	struct Change {int child, parent, oldParentSize;};
	
    vi parent, sz; int comps;
    vector<Change> history;

    DisjointSetRollback(int n) : parent(n), sz(n, 1), comps(n){
        iota(all(parent), 0);
    }

    int findSet(int x){
		while(x != parent[x]) x = parent[x];
		return x;
    }

    void unionSet(int x, int y){
        x = findSet(x); y = findSet(y);
		if(x == y){return;}    
		
        if(sz[x] < sz[y]) swap(x, y);
		history.pb({y, x, sz[x]});
		
		parent[y] = x;
		sz[x] += sz[y];	
        comps--;
    }

    bool same(int x, int y) {return findSet(x) == findSet(y);}
    
    int snapshot() {return SIZE(history);}
    
    void rollback(int snap){
		while(SIZE(history) > snap){
			Change c = history.back(); history.pop_back();
			parent[c.child] = c.child;
			sz[c.parent] = c.oldParentSize;
			comps++;
		}
	}
};
