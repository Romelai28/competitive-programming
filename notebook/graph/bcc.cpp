struct BCC {
	int timer = 0, n;
	vb is_ariculation_point;
	vi num, low, st;  // num es discovery time. (disc)
	vvi comps;
	BCC(const vvi &ady) : n(SIZE(ady)), is_ariculation_point(n), num(n), low(n) { forn(i, n) if (!num[i]) dfs(ady, i); }
private:
	void dfs(const vvi &adj, int u, int p = -1) {
		num[u] = low[u] = ++timer;
		st.push_back(u);
		for (auto v : adj[u]) {
			if (v == p) continue;
			if (num[v]) { low[u] = min(low[u], num[v]); continue;}
			dfs(adj, v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] >= num[u]) {
				is_ariculation_point[u] = (num[u] > 1 || num[v] > 2);
				comps.push_back({u});
				while (comps.back().back() != v) {
					comps.back().push_back(st.back());
					st.pop_back();
				}
			}
		}
	}
};
