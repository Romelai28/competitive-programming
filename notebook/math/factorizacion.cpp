// Factorizar un numero n, cuesta calcular la # de primos <= sqrt(n)
// Hay que llamar a la criba de eratostenes antes (con la cota correcta de primos calculados)
vii factorizar_primos(ll a){
	vii factorizacion_primos;
	for (ll p : primes){
		int potencia = 0;
		if (a == 1) break;
		while (a % p == 0){ a /= p; potencia++;}
		if (potencia > 0) factorizacion_primos.pb({p, potencia});
	}
	if (a != 1) factorizacion_primos.pb({a, 1}); // Si no es 1 despues de haberlo dividido por los primos de hasta sqrt(a), entonces es un primo > sqrt(a) de potencia 1
	return factorizacion_primos;
}

// ############################################################### //
// Factorizacion en primos con linear sieve
set<ll> factores_primos(int x){
	set<ll> res;
	while (x > 1){
	   res.insert(lp[x]);
	   x /= lp[x];
	}
	return res;
}


