struct BlockCutTree{
	vi id;  // Dado un nodo v de G, te dice a que nodo pertenece en el block-cut tree de G.
	vi size_comps;  // Dado un v en el block-cut tree, dice cuantos vertices de G estan en la componente biconexa que representa. (-1 si es AP).
	vvi ady_BCT;
	BlockCutTree(const BCC &bcc){
		vvi comps = bcc.comps;
		id.resize(bcc.n);
		int node_id = 0;
		forn(v, bcc.n){
			if(bcc.is_ariculation_point[v]){
				id[v] = node_id++;
				ady_BCT.pb({}); size_comps.pb(UNDEFINED);
			}
		}
		for(auto &comp : bcc.comps){
			int node = node_id++;
			ady_BCT.pb({}); size_comps.pb(UNDEFINED);
			for(int v : comp){
				if(!bcc.is_ariculation_point[v]){
					id[v] = node;
					size_comps[node] = SIZE(comp);
				} else {
					ady_BCT[node].pb(id[v]);
					ady_BCT[id[v]].pb(node);
				}
			}
		}
	}
};
