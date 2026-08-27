using matrix_t = int;
struct Mat {
	int n, m; vv<matrix_t> a;
	Mat() { }
	// Inicializa matriz de nxm con todos 0.
	Mat(int _n, int _m){
		n = _n; m = _m;
		a.assign(n, vector<matrix_t>(m, 0));
	}
	// Inicializa una matriz a partir de un vector.
	Mat(const vv<matrix_t> &v){
		n = SIZE(v);
		m = n ? SIZE(v[0]) : 0;
		a = v;
	}
	// Constructor de la identidad. (Mat I = Mat::identity(4);)
	static Mat identity(int _n) {
		Mat res(_n, _n);
		forn(i, _n) {res.a[i][i] = 1;}
		return res;
	}
	Mat operator + (const Mat &b) {
		assert(n == b.n && m == b.m);
		Mat ans = Mat(n, m);
		forn(i, n) forn(j, m) {ans.a[i][j] = (a[i][j] + b.a[i][j]) % MOD;}
		return ans;
    }
    Mat operator - (const Mat &b) {
		assert(n == b.n && m == b.m);
		Mat ans = Mat(n, m);
		forn(i, n) forn(j, m) {ans.a[i][j] = (a[i][j] - b.a[i][j] + MOD) % MOD;}
		return ans;
    }
    Mat operator * (const Mat &b) {
		assert(m == b.n);
		Mat ans = Mat(n, b.m);
		forn(i, n) forn(j, b.m) forn(k, m) {ans.a[i][j] = (ans.a[i][j] + 1LL * a[i][k] * b.a[k][j] % MOD) % MOD;}
		return ans;
	}
	Mat pow(ll expo) {
		assert(n == m);
		Mat ans = identity(n);
		Mat t(a);
		while (expo) {
			if (expo & 1) {ans = ans * t;}
			t = t * t;
			expo >>= 1;
		}
		return ans;
	}
};
// Min-plus (tropical) matrix multiplication:
//   (A * B)[i][j] = min_k(A[i][k] + B[k][j])
// Identity: 0 on diagonal, INF elsewhere.
// A^k[i][j] = minimum cost of a path of exactly k edges.
// Producto pasa a ser la Suma. Suma pasa a ser el Min.