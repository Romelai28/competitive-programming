#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> edge;
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

#define DBG(x) cerr << #x << " = " << (x) << endl
#define RAYA cerr << "----------" << endl
#define forn(i,n) for (int i=0;i<(int)(n);i++)
#define forsn(i,s,n) for (int i=(s);i<(int)(n);i++)
#define dforn(i,n) for(int i=(int)((n)-1);i>=0;i--)
#define dforsn(i,s,n) for(int i=(int)((n)-1);i>=(int)(s);i--)
#define all(c) (c).begin(),(c).end()

void dfs(ll v, vector<vector<ll>> &ady, vector<bool> &vis){
    vis[v] = true;
    for(ll u : ady[v]){
        if (!vis[u]){
            dfs(u, ady, vis);
        }
    }
}

// DFS que me dice si existe un ciclo en un grafo (no dirigido) y en caso de existir, retorna la back-edge
pair<bool, edge> hasCycle(int v, vector<vector<int>> &adjList, vector<bool> &visited, vector<int> &parents){ 
    visited[v] = true;
    edge e = {UNDEFINED, UNDEFINED};
    pair<bool, edge> res = {false, e};

    for (int i = 0; i < adjList[v].size(); i++){
        int w = adjList[v][i];
        if (!visited[w]){
            parents[w] = v;
            res = hasCycle(w, adjList, visited, parents);
            if (res.first){
                break;
            }
        } else if (visited[w] && parents[v] != w && parents[v] != UNDEFINED){
            edge backEdge = {w,v};
            return {true, backEdge};
        }
    }

    return res;
}