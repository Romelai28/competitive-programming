cin >> s; n = s.size();
nn = 2 * n + 1;
ss = string(nn, '#');
forn(i, n) ss[2*i+1] = s[i];

for (int i = 0, r = 0, c = 0; i < nn; ++i)
{
    int len = r > i ? min(r - i, p[c - i + c]) : 0;
    while (i + len < nn and i - len >= 0 and ss[i+len] == ss[i-len])
        len++;
    p[i] = len;
    if (i + len > r) r = i + len, c = i;
} // Complejidad O(n)