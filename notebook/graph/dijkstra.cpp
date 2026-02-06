using peso = ll;
using indice_nodo = ll;
using nodo_pesado = pair<peso, indice_nodo>;

// Devuelve el vector de distancias desde inicio al i-esimo vertice.
vl dijkstra(indice_nodo inicio, vector<vector<nodo_pesado>> &ady){
    vl distancia(SIZE(ady), LINF); // parent(SIZE(ady), UNDEFINED);
    vb vis(SIZE(ady), false);

    distancia[inicio] = 0;
    set<nodo_pesado> q;
    q.insert({0, inicio});

    while(!q.empty()){
        ll v = q.begin() -> second; q.erase(q.begin());
        if (vis[v]) continue;
        vis[v] = true;
        for(auto p : ady[v]){
            ll longitud = p.fst, u = p.snd;
            if(distancia[v] + longitud < distancia[u]){
                q.erase({distancia[u], u});
                distancia[u] = distancia[v] + longitud;
                // parent[u] = v;
                q.insert({distancia[u], u});
            }
        }
    }
    return distancia;
}
 