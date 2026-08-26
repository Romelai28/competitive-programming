struct PrefixSum2D {
	vector<vl> prefix;
	int n, m;
	
	PrefixSum2D(const vector<vl> &mat){
		n = SIZE(mat); m = SIZE(mat[0]);
		prefix.assign(n+1, vl(m+1, 0));
		forn(i, n) forn(j, m) prefix[i+1][j+1] = prefix[i+1][j] + prefix[i][j+1] - prefix[i][j] + mat[i][j];
	}
	
	ll get_range_sum(int a, int b, int A, int B) const {
		return prefix[A+1][B+1] - prefix[a][B+1] - prefix[A+1][b] + prefix[a][b];
	}
};

struct PrefixSum3D {
	vector<vector<vl>> prefix;
	int n, m, l;
	
	PrefixSum3D(const vector<vector<vl>> &mat){
		n = SIZE(mat); m = SIZE(mat[0]); l = SIZE(mat[0][0]);
		prefix.assign(n+1, vector<vl>(m+1, vl(l+1, 0)));
		forn(i, n) forn(j, m) forn(k, l) {
			prefix[i+1][j+1][k+1] = prefix[i+1][j+1][k] + prefix[i+1][j][k+1] + prefix[i][j+1][k+1] - prefix[i+1][j][k] - prefix[i][j+1][k] - prefix[i][j][k+1] + prefix[i][j][k] + mat[i][j][k];
		}
	}
    
	ll get_range_sum(int x1, int y1, int z1, int x2, int y2, int z2) const {
		return prefix[x2+1][y2+1][z2+1] - prefix[x1][y2+1][z2+1] - prefix[x2+1][y1][z2+1] - prefix[x2+1][y2+1][z1] + prefix[x1][y1][z2+1] + prefix[x1][y2+1][z1] + prefix[x2+1][y1][z1] - prefix[x1][y1][z1];
	}	
};
