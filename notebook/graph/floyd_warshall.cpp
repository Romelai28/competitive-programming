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

// La matriz tuvo que ser inicializada como:
// d(s,v) = w(s,v) si existe
// d(s,v) = 0   si s = v
// d(s,v) = INF si no

void floyd_warshall (ll n, vector<vector<ll>> &matrizDist){
    // matrizDist en la entrada era la matriz de distancias diractas, luego del algoritmo queda calculada en ella APSP. (Distancias minimas i->j)
    for (ll k = 0; k < n; ++k) {
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < n; ++j) {
                if (matrizDist[i][k] < LINF && matrizDist[k][j] < LINF){
                    matrizDist[i][j] = min(matrizDist[i][j], matrizDist[i][k] + matrizDist[k][j]);
                }
            }
        }
    }
}
