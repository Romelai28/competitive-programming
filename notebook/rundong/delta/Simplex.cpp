const ld eps = 1e-10;   // 1e-8
const ld INF = 1e100;

struct LPSolver {       // Deepseek's code
	int m, n;
	vector<int> B, N;
	vector<vld> D;
	
	LPSolver(const vector<vld>& A, const vld& b, const vld& c) {
		m = b.size();   // maximize c^t x such that Ax <= b, x >= 0
		n = c.size();   // A: mxn   c: n
		B.resize(m);
		N.resize(n + 1);
		D.assign(m + 2, vld(n + 2, 0));

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				D[i][j] = A[i][j];

		for (int i = 0; i < m; i++) {
			B[i] = n + i;
			D[i][n] = -1;
			D[i][n + 1] = b[i];
		}

		for (int j = 0; j < n; j++) {
			N[j] = j;
			D[m][j] = -c[j];
		}

		N[n] = -1;
		D[m + 1][n] = 1;
	}

	void Pivot(int r, int s) {
		ld inv = 1.0 / D[r][s];
		for (int i = 0; i < m + 2; i++)
			if (i != r)
				for (int j = 0; j < n + 2; j++)
					if (j != s)
						D[i][j] -= D[r][j] * D[i][s] * inv;

		for (int j = 0; j < n + 2; j++)
			if (j != s) D[r][j] *= inv;

		for (int i = 0; i < m + 2; i++)
			if (i != r) D[i][s] *= -inv;

		D[r][s] = inv;
		swap(B[r], N[s]);
	}

	bool Simplex(int phase) {
		int x = (phase == 1 ? m + 1 : m);
		while (true) {
			int s = -1;
			for (int j = 0; j <= n; j++) {
				if (phase == 2 && N[j] == -1) continue;
				if (s == -1 ||
					D[x][j] < D[x][s] - eps ||
					(fabsl(D[x][j] - D[x][s]) < eps && N[j] < N[s]))
					s = j;
			}

			if (D[x][s] > -eps) return true;

			int r = -1;
			for (int i = 0; i < m; i++) {
				if (D[i][s] < eps) continue;
				if (r == -1 ||
					D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] - eps ||
					(fabsl(D[i][n + 1] / D[i][s] - D[r][n + 1] / D[r][s]) < eps &&
					 B[i] < B[r]))
					r = i;
			}

			if (r == -1) return false;
			Pivot(r, s);
		}
	}

	ld Solve(vld& x) {
		int r = 0;
		for (int i = 1; i < m; i++)
			if (D[i][n + 1] < D[r][n + 1]) r = i;

		if (D[r][n + 1] < -eps) {
			Pivot(r, n);
			if (!Simplex(1) || D[m + 1][n + 1] < -eps)
				return -INF;
				
			for (int i = 0; i < m; i++)
				if (B[i] == -1) {
					int s = -1;
					for (int j = 0; j <= n; j++)
						if (s == -1 ||
							D[i][j] < D[i][s] - eps ||
							(fabsl(D[i][j] - D[i][s]) < eps && N[j] < N[s]))
							s = j;
					Pivot(i, s);
				}
		}

		if (!Simplex(2)) return INF;
		x.assign(n, 0);
		for (int i = 0; i < m; i++)
			if (B[i] < n)
				x[B[i]] = D[i][n + 1];
		return D[m][n + 1]; // ans == -INF Infeasible   ans == INF Unbounded
	}
};  // use round when casting to integer