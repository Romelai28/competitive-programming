vector<ll> BM(const vector<ll>& s) {
	vector<ll> C(1, 1), B(1, 1);
	int L = 0, m = 1;
	ll b = 1;
	for (int n = 0; n < s.size(); ++n) {
		ll d = s[n];
		for (int i = 1; i <= L; ++i) d = (d + C[i] * s[n - i]) % MOD;
		if (d == 0) {
			++m;
			continue;
		}
		vector<ll> T = C;
		ll coef = d * power(b, MOD - 2) % MOD;
		if (C.size() < B.size() + m) C.resize(B.size() + m, 0);
		for (int i = 0; i < B.size(); ++i) {
			C[i + m] = (C[i + m] - coef * B[i] % MOD + MOD) % MOD;
		}
		if (2 * L <= n) {
			L = n + 1 - L; B = T; b = d; m = 1;
		} else {
			++m;
		}
	}

	vector<ll> f(L);
	for (int i = 1; i <= L; ++i) {
		f[i - 1] = (MOD - C[i]) % MOD; 
	}
	return f;   // Dados los primeros 2k (2k + algo) terminos de una secuencia
}               // recursiva linear, devuelve los k coeficientes de la recursion