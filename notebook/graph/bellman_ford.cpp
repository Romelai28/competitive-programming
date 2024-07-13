using peso = ll;
using indice_nodo = ll;
using nodo_pesado = pair<peso, indice_nodo>;

struct Edge {
    ll a, b, cost;

    Edge(ll desde, ll hasta, ll c) : a(desde), b(hasta), cost(c) {}
};

// ############################################################### //

// Asume grafo representado como lista de aristas.

bool bellman_ford(ll n, indice_nodo inicio, vector<Edge> &edges, vector<peso> &dist){
    // Devuelve true sii existe un ciclo de longitud negativa.
    // Calcula SSSP en dist.
 
    // Obtiene las distancias más cortas desde inicio hacia todos.
    dist[inicio] = 0;
    for(ll i=0; i<n; i++){
        for(Edge e : edges){
            if(-LINF < dist[e.a] && dist[e.a] < LINF){
                dist[e.b] = min(dist[e.b], dist[e.a] + e.cost);
            }
        }
    }
 
    // Detectar ciclo de longitud negativa.
    for(Edge e : edges){
        if(-LINF < dist[e.a] && dist[e.a] < LINF){
            if (dist[e.a] + e.cost < dist[e.b]){
                return true;
            }
        }
    }
    return false;
}
