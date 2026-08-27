class FenwickTree2D {
	vector<vector<tint>> t;
	int n, m;
	#define lowbit(x) ((x) & -(x))
	
public:
	FenwickTree2D() = default;

	FenwickTree2D(int n, int m) : n(n), m(m) {
		t = vector<vector<tint>>(n + 2, vector<tint>(m + 2, 0));
	}
	
	void add(int x, int y, tint v) {
		while (x <= n) {
			for (int j = y; j <= m; j += lowbit(j)) t[x][j] += v;
			x += lowbit(x);
		}
	}
	
	tint query(int x, int y) {
		tint ans = 0;
		while (x) {
			for (int j = y; j; j -= lowbit(j)) ans += t[x][j];
			x -= lowbit(x);
		}
		return ans;
	}
};

FenwickTree2D t1, t2, t3, t4;

void group_add(tint x, tint y, tint v) {
	t1.add(x, y, v);
	t2.add(x, y, (y-1) * v);
	t3.add(x, y, (x-1) * (y-1) * v);
	t4.add(x, y, (x-1) * v);
}

void Add(int a, int b, int c, int d, tint x) {
	group_add(a, b, x);
	group_add(a, d+1, -x);
	group_add(c+1, b, -x);
	group_add(c+1, d+1, x);
}

tint Query(tint x, tint y) {
	tint tmp = x * t2.query(x, y) - t3.query(x, y) + y * t4.query(x, y);
	tint ans = x * y * t1.query(x, y) - tmp;
	return ans;
}

tint Query(int a, int b, int c, int d) {
	return Query(c, d) - Query(a-1, d) - Query(c, b-1) + Query(a-1, b-1);
}