// Esta funcion se encarga de calcular la longitud del prefijo que es sufijo al mismo tiempo y maximiza la longitud desde la posicion 0 a la j. Este prefijo no puede ser la palabra completa.

vector<int> ComputePrefixFunction(string &pattern){
    int m = pattern.length();
    vector<int> lps(m);

    lps[0] = 0; // Desde la posicion 0 a la 0 no existe un prefijo que sea sufijo (la palabra completa no cuenta) asi que la longitud es 0
    int len = 0; // La longitud del prefijo/sufijo mas largo es 0 de momento
    int j = 1; // Esto me indica hasta que parte de la palabra estoy calculando el prefijo/sufijo

    while (j < m){
        if (pattern[len] == pattern[j]){ // Si el caracter del prefijo y del sufijo matchean, actualizo lps[j] con el valor de len+1 y actualizo estos iteradores
            len++;
            lps[j] = len;
            j++;
        } else{ // Si no matchearon,
            if (len != 0){ // Si mi len > 0, esto quiere decir que desde la posicion pattern[0...len-1] a pattern[j-1-len ... j-1] las cosas coincidian. Entonces, cambio a len con lps[len-1] que seria el caracter que deberia matchear del prefijo/sufijo con pattern[j-1]
                len = lps[len-1];
            } else{ // Si len = 0, entonces lps[j] = 0 y actualizo el j.
                lps[j] = 0;
                j++;
            }
        }
    }

    return lps;
}

int KMP (string &text, string &pattern){
    int n = text.length();
    int m = pattern.length();
    int len = 0; // Caracteres que coincidieron con el patron de momento
    int times = 0; // Contador de apariciones del patron
    vector<int> lpq = ComputePrefixFunction(pattern);

    for (int i = 0; i < n; i++){
        while (len > 0 && pattern[len] != text[i]){
            len = lpq[len-1];
        }

        if (pattern[len] == text[i]){
            len++;
        }

        if (len == m){
            times++;
            len = lpq[len-1];
        }
    }

    return times;
}