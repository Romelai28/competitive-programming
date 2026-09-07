struct intervalo_t {ll start, end;};
bool compare(const intervalo_t & a, const intervalo_t & b) {
	if (a.start == b.start) {return a.end < b.end;}
	return a.start > b.start;
}
// Calcula, dado un conjunto de intervalos, la maxima cantidad de intervalos que cumplen que formen una cadena de contencion.  // O(n*log(n))
// Donde la contencion es NO es estricta. Asume que el vector intervals sea no vacio.
// Algoritmo basado en calcular la LIS de los puntos finales una vez ordenados los intervalos.
int calcular_maximal_nested_intervals(vector<intervalo_t> &intervals){
	sort(all(intervals), compare);
	vector<ll> lis;
	lis.pb(intervals[0].end);
	for(int i=1; i<SIZE(intervals); i++){
		ll end = intervals[i].end;
		if(lis.back() <= end){
			lis.pb(end);
		} else {
			ll low = upper_bound(all(lis), end) - lis.begin();
			lis[low] = end;
		}
	}
	return SIZE(lis);
}
