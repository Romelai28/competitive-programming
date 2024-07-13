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

void dfs(int v, vector<vector<int>> &ady, vector<bool> &vis){
    vis[v] = true;
    for(int u : ady[v]){
        if (!vis[u]){
            dfs(u, ady, vis);
        }
    }
}


int main()
{
    // Lectura inputs:
    int n, m;
    cin >> n >> m;

    // Trabajo con los indices del [1,...,n]
    int contador = 0;
    vector<pair<int,int>> puentes;
    vector<vector<int>> ady(n+1);
    vector<bool> vis(n+1, false);

    // Representación del grafo como lista de adyacencia.
    for(int i=0; i<m; i++){
        int a, b;
        cin >> a >> b;
        ady[a].pb(b);
        ady[b].pb(a);
    }

    // Resuelvo:
    dfs(1, ady, vis);

    for(int i=2; i<=n; i++){
        if (!vis[i]){
            contador++;
            puentes.pb(make_pair(1,i));
            dfs(i, ady, vis);
        }
    }

    // Output:
    cout << contador << "\n";

    for(pair<int,int> e : puentes){
        cout << e.first << " " << e.second << "\n";
    }

    return 0;
}
