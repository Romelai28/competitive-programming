int h[2*MAXN + 50];
bool key[MAXN];
// main
	cin >> n;
	int x, y;
	repeat(n - 1) cin >> x >> y, G.add_edge(x, y), G.add_edge(y, x);
	dfs1(1, 1, 1);
	for1(i, __lg(n)) for1(v, n) stjmp[i][v] = stjmp[i - 1][stjmp[i - 1][v]];
	int q; cin >> q;
	repeat(q) {
		cin >> m;
		forn(i, m) cin >> qry[i];
		forn(i, m) h[i] = qry[i];
		forn(i, m) key[h[i]] = true;
		sort(h, h + m, [](int i, int j) { return dfn[i] < dfn[j]; });
		cnt = m;
		forn(i, m - 1) h[cnt++] = lca(h[i], h[i + 1]);
		h[cnt++] = 1;
		sort(h, h + cnt, [](int u, int v) { return dfn[u] < dfn[v]; });
		cnt = unique(h, h + cnt) - h;
		forn(i, cnt - 1) VT.add_edge(lca(h[i], h[i + 1]), h[i + 1]);
		
		forn(i, cnt) admin[h[i]] = 0;
		dfs2(1); dfs3(1, 1); dfs4(1, 1); dfs5(1, 1);
		forn(i, cnt) ans[h[i]] = 0; dfs6(1);
		forn(i, m) cout << ans[qry[i]] << ' '; cout << '\n';

		forn(i, cnt) key[h[i]] = false;
		forn(i, cnt) VT.head[h[i]] = 0;
		VT.edge_cnt = 0;
	}
