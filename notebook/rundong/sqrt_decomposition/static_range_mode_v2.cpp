const int MAXN = 5e5 + 3;   // Space constraint 64MB
const int MAXB = 790;

ii sorted_list[MAXN];

int n, m;
int a[MAXN];
int lm[MAXN], rm[MAXN];
int s[MAXN];
int idx[MAXN];
inline int nxt(int i, int k) {
    int j = idx[i];
    if (j + k > rm[j]) return n + 1;
    return s[j + k];
}
inline int prv(int i, int k) {
    int j = idx[i];
    if (j - k < lm[j]) return 0;
    return s[j - k];
}
void build_aux() {
    for1(i, n) sorted_list[i] = { a[i], i };
    sort(sorted_list+1, sorted_list+1 + n);
    for1(i, n) s[i] = sorted_list[i].snd;
    for1(i, n) idx[s[i]] = i;
    for1(i, n)
        if (sorted_list[i].fst != sorted_list[i - 1].fst) lm[i] = i;
        else lm[i] = lm[i - 1];
    for (int i = n; i >= 1; --i)
        if (sorted_list[i].fst != sorted_list[i + 1].fst) rm[i] = i;
        else rm[i] = rm[i + 1];
}

int bsize;
short bi[MAXN];
int bl[MAXB], br[MAXB];
int mode_cnt[MAXB][MAXB];

void build_blocks() {
    bsize = sqrt(n);
    // bsize = 640;
    for (int i = 1, b = 1; i <= n; i += bsize, b++) {
        bl[b] = i;
        br[b] = min(i + bsize - 1, n);
        for (int j = bl[b]; j <= br[b]; ++j)
            bi[j] = b;
    }
    
    for (int b1 = 1; br[b1]; ++b1)
    for (int b2 = b1; br[b2]; ++b2)
    {
        int ans = mode_cnt[b1][b2 - 1];
        for (int i = br[b2]; i >= bl[b2]; --i)
            for (int j = prv(i, ans); j >= bl[b1]; j = prv(j, 1))
                ans++;
        mode_cnt[b1][b2] = ans;
    }
}

int query(int l, int r) {
    if (bi[l] == bi[r]) {
        int ans = 1;
        for (int i = l; i <= r; ++i)
            for (int j = nxt(i, ans); j <= r; j = nxt(j, 1))
                ans++;
        return ans;
    }
    
    int ans = mode_cnt[bi[l] + 1][bi[r] - 1];
    for (int i = l; i <= br[bi[l]]; ++i)
        for (int j = nxt(i, ans); j <= br[bi[r] - 1]; j = nxt(j, 1))
            ans++;
    for (int i = r; i >= bl[bi[r]]; --i)
        for (int j = prv(i, ans); j >= l; j = prv(j, 1))
            ans++;
    return ans;
} // O(n√n + q√n) Time, O(n√n) Space