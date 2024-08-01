// Busqueda ternaria entera sobre [lower, high].

ll l = lower; // extremo izquierdo del rango de búsqueda.
ll r = high; // extremo derecho del rango de búsqueda.
while(l < r) {
    ll mid = (l + r) >> 1;
    if(f(mid) < f(mid+1)) {  // (<) Busca el minimo | (>) Busca el máximo.
        r = mid;
    } else {
        l = mid+1;
    }
}

// Respuesta: f(l).
