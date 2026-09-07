// Devuelve la longitud de la LIS. Asume que valores no es vacio.  O(n*log(n))
// Caso *estrictamente* creciente.
int calcular_LIS(vi &valores){
	vi lis;
	lis.pb(valores[0]);
	forsn(i, 1, n){
		if(lis.back() < valores[i]){  // Para el caso creciente pero no estricto, poner <= y usar upper_bound.
			lis.pb(valores[i]);
		} else {
			int low = lower_bound(all(lis), valores[i]) - lis.begin();
			lis[low] = valores[i];
		}
	}
	return SIZE(lis);
}
