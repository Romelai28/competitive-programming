// Asumiento que quiero hacer una búsqueda binaria en el rango [0, n)
// Importante: chequear el indice porque en caso de que no exista elemento que cumple P(X) puede haber problemas

// Calcular extremo derecho que cumple P(X)
int l = -1; // extremo izquierdo del rango de búsqueda -1
int r = n; // extremo derecho del rango de búsqueda +1
while(r - l > 1) { // mientras que la distancia entre las fronteras sea >1 (es decir, mientras que no estén contiguas)
    int mid = (l + r) / 2;
    if(P(mid)) {
        l = mid;
    } else {
        r = mid;
    }
}
// l es el último elemento que cumple P(X)

// Calcular extremo izquierdo que cumple P(X)
int l = -1; 
int r = n; 
while(r - l > 1) { 
    int mid = (l + r) / 2;
    if(!P(mid)) {
        l = mid;
    } else {
        r = mid;
    }
}

// r es el primer elemento que cumple P(X)
