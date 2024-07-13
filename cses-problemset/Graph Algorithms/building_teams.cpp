#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll UNDEFINED = -1;

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
#define pb push_back

// ############################################################### //

int invertir(int color){
    // Valores color: 1 ó 2.
    if (color == 1){
        return 2;
    } else {
        return 1;
    }
}


bool bfs(int inicio, vector<vector<int>> &ady, vector<bool> &vis, vector<int> &color){
    // Devuelve false si se descubre que NO es bipartito, devuelve true si esa componente conexa es bipartita.
    queue<int> q;
    q.push(inicio);
    vis[inicio] = true;
    color[inicio] = 1;
    while(!q.empty()){
        int v = q.front();  // v es el vértice que estoy procesando
        q.pop();
        for (int u : ady[v]){
            if (!vis[u]){
                vis[u] = true;
                color[u] = invertir(color[v]);
                q.push(u);
            } else {
                if (color[u] == color[v]){return false;}
            }
        }
    }
    return true;
}


int main()
{
    // Lectura inputs:
    int n, m;
    cin >> n >> m;
 
    // Trabajo con los indices del [1,...,n]
    vector<vector<int>> ady(n+1);
    vector<bool> vis(n+1, false);
    vector<int> color(n+1);  // Valores color: 1 ó 2.
 
    // Representación del grafo como lista de adyacencia.
    for(int i=0; i<m; i++){
        int a, b;
        cin >> a >> b;
        ady[a].pb(b);
        ady[b].pb(a);
    }
 
    // Resuelvo:
    bool continuar = true;
 
    for(int i=1; i<=n && continuar; i++){
        if (!vis[i]){
            continuar = bfs(i, ady, vis, color);
        }
    }

    // Output:
    if (!continuar){
        cout << "IMPOSSIBLE";
    } else {
        for (int i=1; i<=n; i++){
            cout << color[i] << " ";
        }
    }
 
    return 0;
}