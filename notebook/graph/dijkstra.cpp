using peso = ll;
using indice_nodo = ll;
using nodo_pesado = pair<peso, indice_nodo>;
 
// ############################################################### //

// Devuelve el vector de distancias desde inicio al i-esimo vértice.
vector<ll> dijkstra(const indice_nodo inicio, const vector<vector<nodo_pesado>> &ady){
    vector<ll> distancia(ady.size(), LINF);
    vector<bool> vis(ady.size(), false);

    distancia[inicio] = 0;
    set<nodo_pesado> q;

    q.insert({0, inicio});

    while(!q.empty()){
        ll v = q.begin() -> second;
        q.erase(q.begin());

        if (vis[v]) {continue;}
        vis[v] = true;
        for(const auto& [longitud, u] : ady[v]){
            // Longitud del camino de v hacia u.
            // Relax:
            if(distancia[v] + longitud < distancia[u]){
                q.erase({distancia[u], u});
                distancia[u] = distancia[v] + longitud;
                q.insert({distancia[u], u});
            }
        }
    }
    return distancia;
}
 