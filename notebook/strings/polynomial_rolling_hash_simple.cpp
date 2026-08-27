const int HASH_K = 2;
const ll HASH_P = 1777771;
ll HASH_MOD[HASH_K] = {999727999, 1070777777};
ll HASH_INV_P[HASH_K] = {325255434, 10018302};
 
vvl hashPow, hashInvPow;
// Llamar a initHash()

void initHash(int maxN){
    hashPow = vvl(HASH_K, vl(maxN + 1, 1));
    hashInvPow = vvl(HASH_K, vl(maxN + 1, 1));
 
    forn(k, HASH_K){
        forsn(i, 1, maxN + 1){
            hashPow[k][i] = (1LL * hashPow[k][i - 1] * HASH_P) % HASH_MOD[k];
            hashInvPow[k][i] = (1LL * hashInvPow[k][i - 1] * HASH_INV_P[k]) % HASH_MOD[k];
        }
    }
}
 
struct Hash {
    vvl pref;
	int n;
	
    Hash(string &s){
        n = SIZE(s);
        pref = vvl(HASH_K, vl(n + 1, 0));
        forn(k, HASH_K) forn(i, n){
            int x = (unsigned char)s[i];
            pref[k][i + 1] = (pref[k][i] + 1LL * x * hashPow[k][i]) % HASH_MOD[k];
        }
    }
 
    ll get(int l, int r){
		assert(0 <= l && l <= r && r < n);

		vl H;
		forn(i, HASH_K) {
			ll h0 = (pref[i][r+1] - pref[i][l] + HASH_MOD[i]) % HASH_MOD[i];
        	h0 = (1LL * h0 * hashInvPow[i][l]) % HASH_MOD[i];
			H.pb(h0);
		}
        return (ll(H[1]) << 32) | ll(H[0]);
    }
};
