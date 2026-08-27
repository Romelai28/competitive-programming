int subtree_size[MAX_N], color[MAX_N], res[MAX_N];
set<int> color_set;
vi nodes_in_subtree[MAX_N];
 
void dfs_size(int v, vb &vis){
	subtree_size[v] = 1;
	vis[v] = true;
	for(auto u : ady[v]){
		if(!vis[u]){
			dfs_size(u, vis);
			subtree_size[v] += subtree_size[u];
		}
	}
}

int get_heavy_child(int v, int parent) {
	int max_size = -1, heavy = UNDEFINED;
	for (int u : ady[v]) {
		if (u != parent && subtree_size[u] > max_size) {
			max_size = subtree_size[u];
			heavy = u;
		}
	}
	return heavy;
}

// Requiere haber completado nodes_in_subtree con dfs_size!
void dsu_on_tree(int v = 0, int p = UNDEFINED, bool keep = false) {
	int heavy = get_heavy_child(v, p);  // aka bigchild.
	// Procesar subarboles livianos.
	for (auto u : ady[v]) {
		if (u != p && u != heavy) {
			dsu_on_tree(u, v, false);
		}
	}
	// Procesar subarbol pesado.
	if (heavy != UNDEFINED) {
		dsu_on_tree(heavy, v, 1);
		swap(nodes_in_subtree[v], nodes_in_subtree[heavy]);
	}
	// Tengo la info de bigchild, ahora agrego la info de v.
	nodes_in_subtree[v].pb(v);
	color_set.insert(color[v]);
	// Ahora agrego la info de los small childs.
	for (auto u : ady[v]) {
		if (u != p && u != heavy) {
			for (auto x : nodes_in_subtree[u]) {
				color_set.insert(color[x]);
				nodes_in_subtree[v].pb(x);
			}
		}
	}
	// Procesar la respuesta. Aca esta la respuesta para el nodo v.
	res[v] = SIZE(color_set);
	// Limpiar si no se debe mantener
	if (!keep) {
		for (auto u : nodes_in_subtree[v]) {
			color_set.erase(color[u]);
		}
	}
}