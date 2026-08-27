// Asumiento que quiero hacer una busqueda binaria en el rango [0, n)
// Importante: chequear el indice porque en caso de que no exista elemento que cumple P(X) puede haber problemas

// Encontrar el indice del elemento v en el array A ordenado
int binarySearch(int start, int end, vector<ll> &A, ll v){
	if (start > end) return -1;

	int mid = start + (end-start)/2;
	if (A[mid] == v) return mid;
	else if (A[mid] < v) return binarySearch(mid+1, end, A, v);
	else return binarySearch(start, mid-1, A, v);
}

int rightBinarySearch(int start, int end){
	int l = start - 1;
	int r = end + 1;

	while (r - l > 1){
		int mid = l + (r-l)/2;
		if (P(mid)) l = mid;
		else r = mid;
	}
	
	if (l < start || l > end || !P(l)) l = -1; // Si l no esta en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
	return l; // l es el ultimo elemento que cumple P(X)
}

int leftBinarySearch(int start, int end){
	int l = start - 1; 
	int r = end + 1; 

	while(r - l > 1) {
		int mid = l + (r-l)/2;
		if(!P(mid)) l = mid;
		else r = mid;
	}
	
	if (r < start || r > end || !P(r)) r = -1; // Si r no esta en el intervalo [start,end] o no cumple la propiedad, entonces retorno -1
	return r; // r es el primer elemento que cumple P(X)
}

auto it1 = lower_bound(all(A), val); // Primer elemento >= val
auto it2 = upper_bound(all(A), val); // Primer elemento > val

// Posibilidades de lower_bound (tambien aplica para upper_bound)
if (it1 == A.end()) // No hay elemento >= val, tengo que retroceder uno a it1 para apuntar al elemento mas grande
if (it1 == A.begin()) // Estoy apuntando al elemento mas chico de A. Si retrocedo, runtime error
