// Busqueda ternaria entera sobre [lower, high].

ll l = lower; // extremo izquierdo del rango de busqueda.
ll r = high; // extremo derecho del rango de busqueda.
while(l < r) {
    ll mid = (l + r) / 2;
    if(f(mid) < f(mid+1)) {  // (<) Busca el minimo | (>) Busca el maximo.
        r = mid;
    } else {
        l = mid+1;
    }
}

// Respuesta: f(l).
