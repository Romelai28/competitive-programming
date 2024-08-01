// Asumiento que quiero hacer una búsqueda binaria en el rango [0, n)

int l = -1; // extremo izquierdo del rango de búsqueda -1
int r = n; // extremo derecho del rango de búsqueda +1
while(r - l > 1) { // mientras que la distancia entre las fronteras sea >1 (es decir, mientras que no estén contiguas)
    int mid = (l + r) >> 1;
    if(P(mid)) {
        l = mid;
    } else {
        r = mid;
    }
}

// Respuesta:
// 'a' la última para cual P da true, y 'b' la primera para la cual P da false.
