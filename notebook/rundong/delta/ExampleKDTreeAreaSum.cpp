const ll INF = 1LL << 60;
int n, m;
ll x[MAXN], y[MAXN], v[MAXN];
int arr[MAXN];
int root, ls[MAXN], rs[MAXN];
ll sum[MAXN], xmin[MAXN], xmax[MAXN], ymin[MAXN], ymax[MAXN];
int compareNode(int i, int j, int dimension) {
   ll v1 = dimension == 0 ? x[i] : y[i];
   ll v2 = dimension == 0 ? x[j] : y[j];
   return v1 == v2 ? 0 : v1 < v2 ? -1 : 1;
}
struct Cmp {
   int dimension;
   bool operator()(int a, int b) const {
       return compareNode(a, b, dimension) < 0;
   }
};
void maintain(int i) {
   sum[i] = v[i] + sum[ls[i]] + sum[rs[i]];
   xmin[i] = min(x[i], min(xmin[ls[i]], xmin[rs[i]]));
   xmax[i] = max(x[i], max(xmax[ls[i]], xmax[rs[i]]));
   ymin[i] = min(y[i], min(ymin[ls[i]], ymin[rs[i]]));
   ymax[i] = max(y[i], max(ymax[ls[i]], ymax[rs[i]]));
}
int build(int l, int r, int dimension) {
   if (l > r) return 0;
   int mid = (l + r) >> 1;
   nth_element(arr + l, arr + mid, arr + r + 1, Cmp{dimension});
   int rt = arr[mid];
   ls[rt] = build(l, mid - 1, dimension ^ 1);
   rs[rt] = build(mid + 1, r, dimension ^ 1);
   maintain(rt);
   return rt;
}
ll query(ll a, ll b, ll c, int i) {
   if (i == 0) return 0;
   ll ax1 = xmin[i] * a;
   ll ax2 = xmax[i] * a;
   ll by1 = ymin[i] * b;
   ll by2 = ymax[i] * b;
   ll minv = min(ax1, ax2) + min(by1, by2);
   ll maxv = max(ax1, ax2) + max(by1, by2);
   if (minv >= c) return 0;
   if (maxv < c) return sum[i];
   ll ans = 0;
   if (a * x[i] + b * y[i] < c) ans += v[i];
   ans += query(a, b, c, ls[i]);
   ans += query(a, b, c, rs[i]);
   return ans;
}
// main
   cin >> n >> m;
   for (int i = 1; i <= n; i++) {
       cin >> x[i] >> y[i] >> v[i];
       arr[i] = i;
   }
   xmin[0] = ymin[0] = INF;
   xmax[0] = ymax[0] = -INF;
   root = build(1, n, 0);
   ll a, b, c;
   for (int i = 1; i <= m; i++) {
       cin >> a >> b >> c;  // suma de pesos de todos los puntos (x, y) tales
       cout << query(a, b, c, root) << "\n";    // que ax + by < c
   }
