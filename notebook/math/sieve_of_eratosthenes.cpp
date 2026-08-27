// O(MAX_N log(log(MAX_N)))

const ll COTA_SUP_N = 110000;
vector<bool> is_prime(COTA_SUP_N+1, true);
 
void sieveOfEratosthenes(){
	is_prime[0] = false;
	is_prime[1] = false;
	for (ll i = 2; i <= COTA_SUP_N; i++) if (is_prime[i]) 
		for (ll j = i*i; j <= COTA_SUP_N; j += i) is_prime[j] = false;
}