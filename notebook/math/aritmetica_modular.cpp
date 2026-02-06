ll mod(ll a, ll m = MOD){
	ll res = a % m;
    if (res < 0) res += m;
	return res;
}
 
ll divideMod(ll a, ll b, ll m = MOD){
    ll res = mulMod(a, binPowMod(b, m-2, m), m) % m;
    return res;
}

ll combinatorial_func(ll n, ll k, ll m = MOD){
	return divideMod(fact[n], mulMod(fact[k], fact[n-k], m), m);
}

