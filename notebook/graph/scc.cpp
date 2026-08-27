struct SCC {
	int n, comps = 0;
	vb vis;
	vi order, id_scc;  // id_scc[v] = id de la componente fuertemente conexa a la que pertenece v.
	vvi ady, ady_t;
	vi representante;  // (Opcional) Dada un *id_scc*, te dice algun nodo de esa scc.	
	SCC(vvi &_ady, vvi &_ady_t) : ady(_ady), ady_t(_ady_t), n(SIZE(ady)), vis(n, false), id_scc(n) {
		forn(i, n) if(!vis[i]) { dfs1(i); }
		vis.assign(n, false);
		reverse(all(order));
		for(int v : order){
			if(!vis[v]){
				dfs2(v, comps);
				representante.pb(v);
				comps++;
			}
		}
	}
	vvi sccToDAG(){  // (Opcional)
		vector<set<int>> ady_dag_with_set(comps);
		forn(v, n){
			for(int u : ady[v]){
				if(id_scc[v] == id_scc[u]) {continue;}  // Evita self-loops.
				ady_dag_with_set[id_scc[v]].insert(id_scc[u]);
			}
		}
		vvi ady_dag(comps);
		forn(i, comps){
			ady_dag[i] = vi(all(ady_dag_with_set[i]));
		}
		return ady_dag;
	}
private:
	void dfs1(int v) {
		vis[v] = true;
		for(int u : ady[v]) {
			if (!vis[u]) { dfs1(u); }
		}
		order.pb(v);
	}
	void dfs2(int x, int comp) {
		vis[x] = true;
		for (int u : ady_t[x]) {
			if (!vis[u]) { dfs2(u, comp); }
		}
		id_scc[x] = comp;
	}
};
