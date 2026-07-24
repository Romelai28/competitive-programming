struct DisjointSet{
    vl parent, rnk;
    ll numOfComponents;

    DisjointSet(ll n){
        rnk.assign(n, 0);
        forn(i, n) parent.pb(i);
        numOfComponents = n;
    }

    ll findSet(ll x){
        if(parent[x]!=x) parent[x] = findSet(parent[x]);
        return parent[x];
    }

    void unionSet(ll x, ll y){
        x = findSet(x); y = findSet(y);
        if (x != y){
            if (rnk[x] < rnk[y]) parent[x] = y;
            else if (rnk[x] > rnk[y]) parent[y] = x;
            else { parent[y] = x; rnk[x]++;}
            numOfComponents--;
        }
    }

    bool same(ll x, ll y){ return findSet(x) == findSet(y);}
};
