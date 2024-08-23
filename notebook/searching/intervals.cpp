// We suppose that the intervals are correct: p.first <= p.second
// The intervals describe this: [p.first, p.second]

// This function checks if the intervals p1 and p2 are disjoint
bool areDisjoint(pair<ll, ll> &p1, pair<ll, ll> &p2) {
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;
    ll startingTimeP2 = p2.first;
    ll endingTimeP2 = p2.second;

    // This option checks supposing that p1 starts before than p2
    bool option1 = endingTimeP1 < startingTimeP2;
    // This option checks supposing that p2 starts before than p1
    bool option2 = endingTimeP2 < startingTimeP1;

    return option1 || option2;
}

// This function checks if p1 is included in p2
bool isIncluded(pair<ll, ll> &p1, pair<ll, ll> &p2){
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;
    ll startingTimeP2 = p2.first;
    ll endingTimeP2 = p2.second;

    bool res = startingTimeP2 <= startingTimeP1 && endingTimeP1 <= endingTimeP2;
    return res;
}

bool belongsToTheInterval(pair<ll, ll> &p1, ll x){
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;

    return startingTimeP1 <= x && x <= endingTimeP1;
}

bool estaALaIzquierda(pair<ll, ll> &p1, pair<ll, ll> &p2){
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;
    ll startingTimeP2 = p2.first;
    ll endingTimeP2 = p2.second;
    bool res1 = startingTimeP2 <= endingTimeP1 && endingTimeP1 <= endingTimeP2;
    bool res2 = endingTimeP1 <= startingTimeP2;

    return res1 || res2;
}

ll intervalSize(pair<ll,ll> &p1){
    ll endingTimeP1 = p1.second;
    ll startingTimeP1 = p2.first;
    ll res = (ll) endingTimeP1 - startingTimeP1 + 1;
    
    if (startingTimeP1 > endingTimeP1){
        res = 0;
    }

    return res;
}

// Chequear que la respuesta sea valida porque en caso de interseccion vacia te devuelve un intervalo invalido
pair<ll,ll> intersectionIntervals(pair<ll,ll> &p1, pair<ll,ll> &p2){
    pair<ll,ll> startingTimeP1 = p1.first;
    pair<ll,ll> endingTimeP2 = p1.second;
    pair<ll,ll> startingTimeP2 = p2.first;
    pair<ll,ll> endingTimeP2 = p2.second;

    pair<ll,ll> res = {max(startingTimeP1, startingTimeP2), min(endingTimeP1, endingTimeP2)};
    return res;
}

// Esta funcion me ordena los intervalos para tener primero a aquellos que terminan antes y en caso de empate al que empieza antes.
bool customCompare(pair<ll, ll> &p1, pair<ll, ll> &p2){
    ll endingTimeP1 = p1.second;
    ll endingTimeP2 = p2.second;

    if (endingTimeP1 < endingTimeP2){
        return true;
    } else if (endingTimeP1 > endingTimeP2){
        return false;
    }

    ll startingTimeP1 = p1.first;
    ll startingTimeP2 = p2.first;

    return startingTimeP1 < startingTimeP2;
}

// Esta funcion me sirve para ordenar los intervalos de forma que tengo primero a los que terminan antes, y en caso de empate al que termina mas tarde lo tengo primero.
// Esto me garantiza que: intervalo[i] e intervalo[i+1] se relacionan como: intervalo[i+1] esta contenido en i, o esta superpuesto con intervalo[i+1] pero tiene una parte que no y que esta a la derecha de este.
// Ademas, si intervalo[i+1] e intervalo[i] son disjuntos se que intervalo[i+k] con k>1 tambien es disjunto con intervalo[i]
bool customCompare2(pair<ll,ll> &p1, pair<ll,ll> &p2){
    ll startingTimeP1 = p1.first;
    ll startingTimeP2 = p2.first;

    if (startingTimeP1 < startingTimeP2){
        return true;
    } else if (startingTimeP1 > startingTimeP2){
        return false;
    }

    ll endingTimeP1 = p1.second;
    ll endingTimeP2 = p2.second;

    return endingTimeP1 > endingTimeP2;
}

ll maximumNumberOfDisjointIntervals(vector<pair<ll, ll>> &intervals){
    int n = intervals.size();
    if (n == 0) return 0;

    sort(all(intervals), customCompare);
    pair<ll, ll> lastInterval = intervals[0];
    int res = 1;

    forsn(i,1,n){
        pair<ll, ll> currentInterval = intervals[i];

        if (areDisjoint(currentInterval,lastInterval)){
            lastInterval = currentInterval;
            res++;
        }
    }

    return res;
}

// Esta funcion se encarga de devolverme un arreglo de intervalos en el que ninguno contiene al otro y se conservan solo los intervalos mas grandes. Es decir, si A1 estaba incluido en A2, agrego a A2 a B
vector<pair<ll,ll>> eliminateRedundantIntervals(vector<pair<ll,ll>> &A){
    vector<pair<ll,ll>> B;
    sort(all(A), customCompare2);
    int n = A.size();

    if (n == 0){
        return B;
    }

    pair<ll,ll> lastInterval = A[0];
    B.pb(lastInterval);

    forsn(i, 1, n){
        if(!isIncluded(A[i], lastInterval)){
            lastInterval = A[i];
            B.pb(lastInterval);
        }
    }

    return B;
}

pair<ll, ll> redundantInterval(vector<pair<ll, ll>> &intervals){
    int n = intervals.size();
    pair<ll, ll> res = {UNDEFINED, UNDEFINED};

    sort(all(intervals), customCompare2);

    forn(i, n-1){
        pair<ll, ll> currentInterval = intervals[i];
        pair<ll, ll> nextInterval = intervals[i+1];

        if (isIncluded(nextInterval, currentInterval)){
            res = nextInterval;
            break;
        } else if (i+2 <= n-1){
            pair<ll, ll> laterInterval = intervals[i+2];

            if (belongsToTheInterval(currentInterval, nextInterval.first)){
                pair<ll,ll> newInterval = {currentInterval.second + 1, nextInterval.second};

                if (isIncluded(newInterval, laterInterval)){
                    res = nextInterval;
                    break;
                }
            }

        }
    }

    return res;
}

ll interseccionMasGrande(vector<pair<ll,ll>> &A, vector<pair<ll,ll>> &B) {
    vector<pair<ll,ll>> A1 = eliminateRedundantIntervals(A);
    vector<pair<ll,ll>> B1 = eliminateRedundantInterals(B);

    int n = A1.size();
    int m = B1.size();
    ll res = 0;

    int i = 0;
    int j = 0;

    while (i < n && j < m){
        ll sizeIntersection = sizeInterval(intersectionIntervals(A1[i], B1[j]));
        res = max(res, sizeIntersection);

        if (isIncluded(A1[i], B1[j])){
            i++;
        } else if (isIncluded(B1[j], A1[i])){
            j++;
        } else if (estaALaIzquierda(A1[i], B1[j])){
            i++;
        } else {
            j++;
        }

    }

    return res;
}