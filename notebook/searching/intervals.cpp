typedef pair<ll, ll> interval;

// Las funciones suponen que los intervalos son validos, es decir: p.first <= p.second
// Los intervalos descritos son de la forma: [p.first, p.second]

// Esta funcion chequea si dos intervalos son disjuntos
bool areDisjoint(interval &p1, interval &p2) {
	ll startingTimeP1 = p1.first, endingTimeP1 = p1.second;
	ll startingTimeP2 = p2.first, endingTimeP2 = p2.second;
	return endingTimeP1 < startingTimeP2 || endingTimeP2 < startingTimeP1;
}

// Esta funcion chequea si p1 esta incluido en p2
bool isIncluded(interval &p1, interval &p2){
	ll startingTimeP1 = p1.first, endingTimeP1 = p1.second;
	ll startingTimeP2 = p2.first, endingTimeP2 = p2.second;
	return startingTimeP2 <= startingTimeP1 && endingTimeP1 <= endingTimeP2;;
}

// Esta funcion chequea si x pertenece al intervalo p1
bool belongsToTheInterval(interval &p1, ll x){
	ll startingTimeP1 = p1.first, endingTimeP1 = p1.second;
	return startingTimeP1 <= x && x <= endingTimeP1;
}

// Esta funcion chequea si el intervalo p1 esta a la izquierda de p2, es decir: p1.second <= p2.first
bool estaALaIzquierda(interval &p1, interval &p2){
	ll endingTimeP1 = p1.second, startingTimeP2 = p2.first;
	return endingTimeP1 <= startingTimeP2;
}

// Esta funcion me retorna el tamano de un intervalo. En caso de que el intervalo sea invalido, retorna 0
ll intervalSize(interval &p1){
	ll endingTimeP1 = p1.second, startingTimeP1 = p2.first;
	ll res = (ll) endingTimeP1 - startingTimeP1 + 1;
	if (startingTimeP1 > endingTimeP1) res = 0;
	return res;
}

// Esta funcion retorna la interseccion entre dos intervalos. Chequear que la respuesta sea valida porque en caso de interseccion vacia te devuelve un intervalo invalido
interval intersectionIntervals(interval &p1, interval &p2){
	ll startingTimeP1 = p1.first, endingTimeP2 = p1.second;
	ll startingTimeP2 = p2.first, endingTimeP2 = p2.second;
	interval res = {max(startingTimeP1, startingTimeP2), min(endingTimeP1, endingTimeP2)};
	return res;
}

// Esta funcion me ordena los intervalos para tener primero a aquellos que terminan antes y en caso de empate al que empieza antes.
bool finishEarlier(interval &p1, interval &p2){
	ll endingTimeP1 = p1.second, endingTimeP2 = p2.second;
	if (endingTimeP1 != endingTimeP2) return endingTimeP1 < endingTimeP2;
	ll startingTimeP1 = p1.first, startingTimeP2 = p2.first;
	return startingTimeP1 < startingTimeP2;
}

// Esta funcion me sirve para ordenar los intervalos de forma que tengo primero a los que empiezan antes, y en caso de empate al que termina mas tarde lo tengo primero.
// Esto me garantiza que: intervalo[i] e intervalo[i+1] se relacionan como: intervalo[i+1] esta contenido en i, o esta superpuesto con intervalo[i+1] pero tiene una parte que no y que esta a la derecha de este.
// Ademas, si intervalo[i+1] e intervalo[i] son disjuntos se que intervalo[i+k] con k>1 tambien es disjunto con intervalo[i]
bool startEarlier(interval &p1, interval &p2){
	ll startingTimeP1 = p1.first, startingTimeP2 = p2.first;
	if (startingTimeP1 != startingTimeP2) return startingTimeP1 < startingTimeP2;
	ll endingTimeP1 = p1.second, endingTimeP2 = p2.second;
	return endingTimeP1 > endingTimeP2;
}

// Esta funcion calcula el maximo numero de intervalos disjuntos
ll maximumNumberOfDisjointIntervals(vector<interval> &intervals){
	int n = SIZE(intervals);
	if (n == 0) return 0;

	sort(all(intervals), finishEarlier);
	interval lastInterval = intervals[0];
	ll res = 1;

	forsn(i,1,n){
		interval currentInterval = intervals[i];
		if (areDisjoint(currentInterval,lastInterval)){
			lastInterval = currentInterval;
			res++;
		}
	}

	return res;
}

// Esta funcion se encarga de devolverme un arreglo de intervalos en el que ninguno contiene al otro y se conservan solo los intervalos mas grandes. Es decir, si A1 estaba incluido en A2, agrego a A2 a B
vector<interval> eliminateRedundantIntervals(vector<interval> &A){
	vector<interval> B;
	sort(all(A), startEarlier);
	int n = SIZE(A);

	if (n == 0) return B;
	
	interval lastInterval = A[0];
	B.pb(lastInterval);

	forsn(i, 1, n){
		if(!isIncluded(A[i], lastInterval)){
			lastInterval = A[i];
			B.pb(lastInterval);
		}
	}

	return B;
}

// Esta funcion me retorna un intervalo redundante de mi arreglo. Un intervalo esta redundante si esta contenido entre 1 o mas intervalos del arreglo
interval redundantInterval(vector<interval> &intervals){
	int n = SIZE(intervals);
	interval res = {UNDEFINED, UNDEFINED}; // Inicialmente supongo que no existe intervalo redundante
	sort(all(intervals), startEarlier);

	forn(i, n-1){
		interval currentInterval = intervals[i], nextInterval = intervals[i+1];

		if (isIncluded(nextInterval, currentInterval)){ // Si el intervalo siguiente esta contenido en el actual, entonces es redundante
			res = nextInterval;
			break;
		} else if (i+2 <= n-1){ // Si el intervalo siguiente no esta contenido en el actual, chequeo si esta contenido entre el actual y el siguiente a el
			interval laterInterval = intervals[i+2];

			if (belongsToTheInterval(currentInterval, nextInterval.first)){ // Chequeo si una parte del intervalo siguiente esta contenido en el actual
				// Esto es lo que me falta contener del intervalo siguiente
				interval newInterval = {currentInterval.second + 1, nextInterval.second};

				if (isIncluded(newInterval, laterInterval)){ // Chequeo si dicha parte esta contenido en el intervalo siguiente a el
					res = nextInterval;
					break;
				}
			}

		}
	}

	return res;
}

ll biggestIntersection(vector<interval> &A, vector<interval> &B) {
	vector<interval> A1 = eliminateRedundantIntervals(A), B1 = eliminateRedundantInterals(B);
	int n = SIZE(A1), m = SIZE(B1);
	ll res = 0;
	int i = 0, j = 0;
	
	while (i < n && j < m){
		ll sizeIntersection = sizeInterval(intersectionIntervals(A1[i], B1[j]));
		res = max(res, sizeIntersection);
		
		// Si un intervalo p1 esta incluido en p2, entonces p2 va a ser mas util para la siguiente busqueda ya que es mas grande que p1. Por lo tanto, lo voy a guardar y voy a adelantar al arreglo que contenia a p1
		if (isIncluded(A1[i], B1[j])){ // En este caso, es preferible continuar con el siguiente intervalo de A ya que el de B es mas grande
			i++;
		} else if (isIncluded(B1[j], A1[i])){
			j++;
		// Si un intervalo p1 esta a la izquierda de un intervalo p2, entonces voy a mantener a p2 y adelantar al arreglo de p1 ya que el siguiente intervalo de dicho arreglo podria tener una mejor interseccion con p1
		} else if (estaALaIzquierda(A1[i], B1[j])){
			i++;
		} else {
			j++;
		}
	}

	return res;
}

int biggestIntersectionOfIntervals(vector<interval> &A){
	int res = 0, currentRes = 0;

	vector<pair<ll, int>> B;
	forn(i, SIZE(A)){
		B.pb({A[i].fst, 1});
		B.pb({A[i].snd, -1});
	}

	forn(i, SIZE(B)){
		currentRes += B[i].snd;
		res = max(res, currentRes);
	}

	return res;
}