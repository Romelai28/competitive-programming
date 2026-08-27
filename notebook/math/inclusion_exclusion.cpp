struct InclusionExclusion{
	ll k, n;
	vl A;

	InclusionExclusion(ll K, ll N, vl &a) : k(K), n(N), A(a) {}

	// Quiero ver la # elementos que cumplen P(x) en la union de los conjuntos: A[0], A[1], ..., A[k-1]
	ll sizeIntersection(ll mask){
		ll res = 0, divisor = 1;
		int j = 0;

		while (mask > 0){
			if (mask & 1){
				if (divisor > n/A[j]){ divisor = 0; break; }
				else divisor *= A[j];
			}
			j++;
			mask = mask >> 1;
		}

		if (divisor > 0) res += n/divisor;
		return res;
	}
	
	ll solve(){
		ll res = 0, cota = 1ll << k;
		forsn(mask, 1, cota){
			ll sizeSet = (ll) __builtin_popcount(mask);
			if (sizeSet % 2 == 0) res -= sizeIntersection(mask);
			else res += sizeIntersection(mask);
		}
		return res;
	}
};