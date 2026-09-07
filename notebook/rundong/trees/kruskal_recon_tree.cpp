class DSU {
	vi p, s, v;
public:
	DSU(int n) : p(n+1), s(n+1, 1), v(n+1) { for1(i, n) p[i] = v[i] = i; }
	int find(int i) { return i == p[i] ? i : p[i] = find(p[i]); }
	bool unite(int i, int j, int c) {
		i = find(i); j = find(j);
		if (i == j) return false;
		if (s[i] > s[j]) swap(i, j);
		int u = ++nV;
		chi[u][0] = v[i], chi[u][1] = v[j];
		wei[u] = c; pa[u] = pa[v[i]] = pa[v[j]] = u;
		v[j] = u;
		s[j] += s[i], p[i] = j;
		return true;
	}
};