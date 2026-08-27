// Devuelve la longitud de la LIS. Asume que valores no es vacio.  O(n*log(n))
// Caso *estrictamente* creciente.
int calcular_LIS(vector<int> &valores){
	vector<int> lis;
	lis.pb(valores[0]);

	for(int i=1; i<n; i++){
		if(lis.back() < valores[i]){  // Para el caso creciente pero no estricto, poner <= y usar upper_bound.
			lis.pb(valores[i]);
		} else {
			int low = lower_bound(all(lis), valores[i]) - lis.begin();
			lis[low] = valores[i];
		}
	}

	return SIZE(lis);
}

// Calcula la LIS de un arbol que termina en un vertice dado
int binary_search(vector<int>& A, int i, int j, int k){
	if (i >= j) return j;
 
	int middle = (i/2) + (j/2);
 
	if (A[middle] == k){
		return middle;
	} else if (k < A[middle]){
		return binary_search(A, i, middle, k);
	} else {
		return binary_search(A, middle + 1, j, k);
	}
}

void dfs(int v, vector<int> &res, vector<vector<int>> &adjList, vector<int> &lis, vector<int> &val){
	visited[v] = true;
	res[v] = SIZE(lis);
	
	for (int w : adjList[v]){
		if (!visited[w]){
			if (val[w] > lis.back()){
				lis.pb(val[w]);
				dfs(w, res, adjList, lis, val);
				lis.pop_back();
			} else {
				int positionElementIth = binary_search(lis, 0, SIZE(lis)-1, val[w]);
				int oldValue = lis[positionElementIth];
				lis[positionElementIth] = val[w];
				dfs(w, res, adjList, lis, val);
				lis[positionElementIth] = oldValue;
			}
		}
	}
}

vector<int> lis;
lis.pb(val[1]);
dfs(1, res, adjList, lis, val);
