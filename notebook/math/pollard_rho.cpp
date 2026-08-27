// Ojo: En mulMod castear a __int128.
bool miller(ll n) { // Determina si n es primo
	if (n < 2) return false;
	for (ll p : {2, 3, 5, 7, 11, 13, 17, 19}) if (n % p == 0) return n == p;
	if (n < 529) return true;
	int s = 0;
	ll d = n - 1;
	while (d % 2 == 0) d /= 2, s ++;
	auto witness = [&](ll a) {
		ll x = binPowMod(a%n, d, n);
		if (x == 0) return true;
		if (x == 1 or x == n - 1) return false;
		forsn(_, 1, s) {
			x = mulMod(x, x, n);
			if (x == n - 1) return false;
			if (x < 2) return true;
		}
		return true;
	};
	for (ll b : {2, 325, 9'375, 28'178, 450'775, 9'780'504, 1'795'265'022})
		if (witness(b)) return false;
	return true;
}
ll rho(ll n) {
	if(n % 2 == 0) return 2;
	ll x = 2, y = 2, d = 1;
	ll c = rand() % n + 1;
	while(d == 1) {
		x = (mulMod(x, x, n) + c) % n;
		y = (mulMod(y, y, n) + c) % n;
		y = (mulMod(y, y, n) + c) % n;
		d = gcd(x - y, n);
	}
	return d == n ? rho(n) : d;
}
void fact(ll n, unordered_map<ll, int>& F) { // Agrega los factores de n en F
	if (n == 1) return;
	if (miller(n)) {F[n]++; return;}
	ll q = rho(n); fact(q, F); fact(n / q, F);
}