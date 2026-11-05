struct xor_basis {
	vl basis;
	xor_basis() {};
	ll generate(ll x) {
		for(auto y : basis) x = min(x, x^y);
		return x;
	}
	void add(ll x) {
		x = generate(x);
		if(x) basis.pb(x);
	}
	bool contains(ll x) {return generate(x) == 0LL;}
	int dimension() {return SIZE(basis);}
};