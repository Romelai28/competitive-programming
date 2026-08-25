int a1[MAXN][MAXB];
int range_le(int b1, int b2, int k) {
    return a1[k][b2] - a1[k][b1 - 1];
}
ii a2[MAXN];
ll a3[MAXB][MAXB];
int pre[MAXN], suf[MAXN];

struct FenwickTree { ... } ft;

int c1, c2;
int t1[MAXB], t2[MAXB];
int f(int b1, int l1, int r1, int b2, int l2, int r2) {
    c1 = c2 = 0;
    forib(i, b1) {
        t1[c1] = a2[i].fst;
        c1 += l1 <= a2[i].snd and a2[i].snd <= r1;
    }
    forib(i, b2) {
        t2[c2] = a2[i].fst;
        c2 += l2 <= a2[i].snd and a2[i].snd <= r2;
    }
        
    int ans = 0;
    int i = 0, j = 0;
    while (i < c1 and j < c2)
        if (t1[i] < t2[j])
            i++;
        else
            ans += c1 - i,
            j++;
    return ans;
}

void build() {
    block_size = 160;
    for (int i = 1, b = 1; i <= n; i += block_size, b++, block_cnt++) {
        bl[b] = i;
        br[b] = min(i + block_size - 1, n);
        for (int j = i; j <= br[b]; ++j) bi[j] = b;
    }
    
    for1(i, n) a1[a[i]][bi[i]]++;
    for1(i, n) forb(b) a1[i][b] += a1[i - 1][b];
    for1(i, n) forb(b) a1[i][b] += a1[i][b - 1];
        
    for1(i, n) a2[i] = { a[i], i };
    forb(b) sort(a2 + bl[b], a2 + br[b] + 1);
    
    forb(b) {
        forba(i, br[b], bl[b])
            a3[b][b] += ft.query(a[i]), ft.add(a[i], 1);
        forib(i, b) ft.add(a[i], -1);
    }
    
    forb(b2) for (int b1 = b2 - 1; b1 >= 1; --b1) {
        a3[b1][b2] = a3[b1 + 1][b2] + a3[b1][b1];
        forib(i, b1) a3[b1][b2] += range_le(b1 + 1, b2, a[i]);
    }
    
    forb(b) {
        forib(i, b) {
            if (i > bl[b]) pre[i] = pre[i - 1];
            pre[i] += i - bl[b] - ft.query(a[i]);
            ft.add(a[i], 1);
        }
        forib(i, b) ft.add(a[i], -1);
        
        forba(i, br[b], bl[b]) {
            if (i < br[b]) suf[i] = suf[i + 1];
            suf[i] += ft.query(a[i]);
            ft.add(a[i], 1);
        }
        forib(i, b) ft.add(a[i], -1);
    }
}

ll query(int l, int r) {
    if (bi[l] == bi[r]) {
        if (l == bl[bi[l]]) return pre[r];
        return pre[r] - pre[l - 1] - f(bi[l], bl[bi[l]], l - 1, bi[r], l, r);
    }
    
    int b1 = bi[l] + 1, b2 = bi[r] - 1;
    ll ans = a3[b1][b2] + suf[l] + pre[r];
    forab(i, l, br[bi[l]]) ans += range_le(b1, b2, a[i]);
    forab(i, bl[bi[r]], r) ans += br[b2] - bl[b1] + 1 - range_le(b1, b2, a[i]);
    ans += f(bi[l], l, br[bi[l]], bi[r], bl[bi[r]], r);
    return ans;
}