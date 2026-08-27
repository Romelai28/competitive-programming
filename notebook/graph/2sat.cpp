// Requiere SCC. // O(n)
struct TwoSat {
	int n_vars, n_vertices;
	vvi ady, ady_t; vb assignment;
	TwoSat(int n) : n_vars(n), n_vertices(2*n), ady(n_vertices), ady_t(n_vertices), assignment(n_vars) {}
	// indexo las variables como: V0, F0, V1, F1, V2, F2 ...
	bool canBeSat(){
		SCC scc(ady, ady_t);
		forn(i, n_vars){
			if(scc.id_scc[2*i] == scc.id_scc[2*i+1]) return false;
			assignment[i] = scc.id_scc[2*i] > scc.id_scc[2*i+1];
		}
		return true;
	}
	void add_disyuncion(int a, bool na, int b, bool nb){
		// na true si tengo que poner (not A) na false si tengo que poner A!
		a = (2*a) ^ na; b = (2*b) ^ nb;
		int neg_a = a ^ 1, neg_b = b ^ 1;
		// A or B <=> ((not B => A) and (not A => B))
		ady[neg_b].pb(a); ady_t[a].pb(neg_b);
		ady[neg_a].pb(b); ady_t[b].pb(neg_a);
	}
};
// Gadgets:
// 1. Forcing a variable to be true: (x or x)
// 2. Exactly one variable to be true: (x or y) and (not x or not y)
// 3. At least one variable to be true: (x or y)
// 4. At most one variable to be true: (not x or not y)
// 5. Both variables must have the same value: (x or not y) and (not x or y)