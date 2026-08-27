const ll COTA_SUP_N = 110000;
int lp[COTA_SUP_N+1];
vi primes;

void linear_sieve(){
	forsn(i, 1, COTA_SUP_N+1) lp[i] = 0;
	
	forsn(i, 2, COTA_SUP_N+1){
		if (lp[i] == 0){
			lp[i] = i;
			primes.pb(i);
		}

		for(int j = 0; i*primes[j] <= COTA_SUP_N; j++) {
			lp[i*primes[j]] = primes[j];
			if (primes[j] == lp[i]) break;
		}
	}
}


