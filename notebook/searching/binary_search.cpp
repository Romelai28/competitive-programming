// Asumiento que quiero hacer una busqueda binaria en el rango [0, n)
// Importante: chequear el indice porque en caso de que no exista elemento que cumple P(X) puede haber problemas

// Calcular extremo derecho que cumple P(X)
int l = -1; // extremo izquierdo del rango de busqueda -1
int r = n; // extremo derecho del rango de busqueda +1
while(r - l > 1) { // mientras que la distancia entre las fronteras sea >1 (es decir, mientras que no esten contiguas)
    int mid = (l + r) / 2;
    if(P(mid)) {
        l = mid;
    } else {
        r = mid;
    }
}
// l es el ultimo elemento que cumple P(X)

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
