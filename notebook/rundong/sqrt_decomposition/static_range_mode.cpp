int n, sqrtn;
int a[MAXN];
int rnk[MAXN];
i16 bi[MAXN];
int bl[MAXB], br[MAXB];
int freq[MAXB][MAXN];
int mode[MAXB][MAXB];
int range_freq(int b1, int b2, int i) {
    if (b1 > b2) return 0;
    return freq[b2][i] - freq[b1 - 1][i];
}
vi coords = { 0 };
void build()
{
    for1(i, n) coords.push_back(a[i]);
    compress(coords);
    for1(i, n) rnk[i] = lower_bound(all(coords), a[i]) - coords.begin();
    
    sqrtn = sqrt(n);
    for (int i = 1, b = 1; i <= n; i += sqrtn, b++) {
        bl[b] = i;
        br[b] = min(n, i + sqrtn - 1);
        for (int j = i; j <= br[b]; ++j)
            bi[j] = b;
    }
    
    for (int b = 1; br[b]; ++b)
    forab(i, bl[b], br[b])
        freq[b][rnk[i]]++;
    
    for (int b = 1; br[b]; ++b)
    for1(i, n)
        freq[b][i] += freq[b - 1][i];
        
    for (int b = 1; br[b]; ++b) {
        int m = 0;
        for (int i = bl[b]; i <= br[b]; ++i) {
            if (range_freq(b, b, rnk[i]) > range_freq(b, b, rnk[m]))
                m = i;
            else if (range_freq(b, b, rnk[i]) == range_freq(b, b, rnk[m])
                and a[i] < a[m])
                m = i;
        }
        mode[b][b] = m;
    }
    
    for (int b = 1; br[b]; ++b)
    for (int c = b + 1; br[c]; ++c)
    {
        int m = mode[b][c - 1];
        for (int i = bl[c]; i <= br[c]; ++i) {
            if (range_freq(b, c, rnk[i]) > range_freq(b, c, rnk[m]))
                m = i;
            else if (range_freq(b, c, rnk[i]) == range_freq(b, c, rnk[m])
                and a[i] < a[m])
                m = i;
        }
        mode[b][c] = m;
    }
}
int aux[MAXN];
int range_mode(int l, int r)
{
    if (bi[l] == bi[r]) {
        int m = 0;
        forab(i, l, r) aux[rnk[i]] = 0;
        forab(i, l, r) aux[rnk[i]]++;
        forab(i, l, r)
            if (aux[rnk[i]] > aux[rnk[m]])
                m = i;
            else if (aux[rnk[i]] == aux[rnk[m]] and a[i] < a[m])
                m = i;
        return m;
    }
    
    int b1 = bi[l] + 1, b2 = bi[r] - 1;
    int m = (b1 > b2) ? 0 : mode[b1][b2];
    
    aux[rnk[m]] = 0;
    forab(i, l, br[bi[l]]) aux[rnk[i]] = 0;
    forab(i, bl[bi[r]], r) aux[rnk[i]] = 0;
    
    forab(i, l, br[bi[l]]) if (not aux[rnk[i]]) aux[rnk[i]] = range_freq(b1, b2, rnk[i]);
    forab(i, bl[bi[r]], r) if (not aux[rnk[i]]) aux[rnk[i]] = range_freq(b1, b2, rnk[i]);
    forab(i, l, br[bi[l]]) aux[rnk[i]]++;
    forab(i, bl[bi[r]], r) aux[rnk[i]]++;
    
    if (not aux[rnk[m]])
        aux[rnk[m]] = range_freq(b1, b2, rnk[m]);
    
    forab(i, l, br[bi[l]])
        if (aux[rnk[i]] > aux[rnk[m]]) m = i;
        else if (aux[rnk[i]] == aux[rnk[m]] and a[i] < a[m]) m = i;
    forab(i, bl[bi[r]], r)
        if (aux[rnk[i]] > aux[rnk[m]]) m = i;
        else if (aux[rnk[i]] == aux[rnk[m]] and a[i] < a[m]) m = i;
    
    return m;
} // O(n√n + q√n) Time, O(n√n) Space