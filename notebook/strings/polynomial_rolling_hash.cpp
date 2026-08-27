// Precomputo: O(|s|)
// Query: O(1)

constexpr int HT_SIZE = ...;  // HT_SIZE == SIZE(M_vec) == SIZE(B_vec)
struct HashedString {
	static constexpr array<ll, HT_SIZE> M_vec = {VALORES};  // MOD, MOD+2, 991831889
	//~ static constexpr array<ll, HT_SIZE> B_vec = {VALORES};  // 31, 53, 9973
	inline static array<ll, HT_SIZE> B_vec = [](){
		mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
		array<ll, HT_SIZE> bases;
		forn(i, HT_SIZE){
			const ll B = uniform_int_distribution<ll>(0.1 * M_vec[i], 0.9 * M_vec[i])(rng);
			bases[i] = B;
		}
		return bases;
	}();
	
	inline static array<vector<ll>, HT_SIZE> potencia;
	array<vector<ll>, HT_SIZE> prefix_hash;

	HashedString(const string &s){
		forn(ht, HT_SIZE){
			const ll M = M_vec[ht], B = B_vec[ht];
			prefix_hash[ht].resize(SIZE(s)+1, 0);

			if(potencia[ht].empty()) { potencia[ht].pb(1); }
			while(SIZE(potencia[ht]) <= SIZE(s)) { potencia[ht].pb(mulMod(potencia[ht].back(), B, M)); }

			prefix_hash[ht][0] = 0;
			forsn(i, 1, SIZE(s)+1) { prefix_hash[ht][i] = addMod(mulMod(prefix_hash[ht][i-1], B, M), (ll)s[i-1], M); }
		}
	}

	array<ll, HT_SIZE> get_hash(int start, int end) const { // [start, end]
		array<ll, HT_SIZE> hash_res;
		forn(ht, HT_SIZE){
			const ll M = M_vec[ht];
			hash_res[ht] = mod(prefix_hash[ht][end + 1] - mulMod(prefix_hash[ht][start], potencia[ht][end - start + 1], M), M);
		}
		return hash_res;
	}
};
