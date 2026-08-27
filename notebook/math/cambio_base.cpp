vi convertFromDecimalToB(ll x, int b){ // Convierto de base 10 a base b
	vi res; // Si esta vacio, es 0
	while (x > 0){ res.pb(x%b); x /= b;}
	return res; // res[0] es el digito menos significativo
}
 
ll convertFromBToDecimal(vi &digits, int b){
	ll res = 0;
	forn(i, SIZE(digits)) res += digits[i]*((ll) pow(b, i));
	return res;
}