using peso = ll;
using indice_nodo = ll;
using nodo_pesado = pair<peso, indice_nodo>;
 
// ############################################################### //

vector<ll> dijkstra(ll n, indice_nodo inicio, vector<vector<nodo_pesado>> &ady){
    // Devuelve el vector de distancias desde inicio al i-esimo vértice.

    vector<ll> distancia(n+1, LINF);
    // vector<ll> parent(n+1, UNDEFINED);
    vector<bool> vis(n+1, false);
 
    distancia[inicio] = 0;
    set<nodo_pesado> q;
 
    q.insert({0, inicio});
 
    while(!q.empty()){
        ll v = q.begin() -> second;
        q.erase(q.begin());
 
        if (vis[v]) {continue;}
        vis[v] = true;
        for(auto edge : ady[v]){
            ll u = edge.second;
            ll longitud = edge.first;  // Longitud del camino de v hacia u.
            // Relax:
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
 