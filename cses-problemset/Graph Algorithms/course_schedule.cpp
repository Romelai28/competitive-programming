#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll UNDEFINED = -1;

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const ll zero = 0;
#define pb push_back
#define fst first
#define snd second
#define esta(x,c) ((c).find(x) != (c).end())  // Devuelve true si x es un elemento de c.

// ############################################################### //

enum Color {WHITE, GREY, BLACK};  // Sin visitar / en proceso / Procesado.

// Devuelve true si encuentra un ciclo.
bool tdfs(ll v, const vector<vector<ll>> &ady, vector<Color> &color, vector<ll> &orden){
    color[v] = GREY;

    for(auto u : ady[v]){
        if(color[u] == GREY){  // Si encuentra un nodo en proceso, hay un ciclo.
            return true;
        }
        else if (color[u] == WHITE){  // Si encuentra un nodo no visitado, realiza DFS.
            if(tdfs(u, ady, color, orden)) return true;
        }
    }

    orden.pb(v);
    color[v] = BLACK;
    return false;
}

// Devuelve true sii existe un ciclo en G.
// Si no existe ciclo, en orden queda almacenado un orden topologico de G.
bool toposort(const vector<vector<ll>> &ady, vector<ll> &orden){
    vector<Color> color(ady.size(), WHITE);
    orden.clear();

    for(ll v=0; v < ady.size(); v++){
        if (color[v] == WHITE){
            if(tdfs(v, ady, color, orden)) return true;
        }
    }

    reverse(orden.begin(), orden.end());
    return false;
}



int main()
{
    // Lectura inputs:
    ll n, m, a, b;

    cin >> n >> m;

    // Represento al grafo como una lista de adyacencia.
    vector<vector<ll>> ady(n);

    for(ll i=0; i<m; i++){
        cin >> a >> b;
        a--; b--;
        ady[a].pb(b);
    }

    // Resuelvo:
    vector<ll> res;
    bool hayCiclo = toposort(ady, res);

    // Output:
    if (hayCiclo){
        cout << "IMPOSSIBLE";
    } else {
        for(ll i=0; i<res.size(); i++){
            cout << ++res[i] << " ";
        }
    }

    return 0;
}
