pair<vi, vi> manacher(string &s) {
    int n = SIZE(s);
    string t = "#";
    for (char c : s) {
        t += c;
        t += '#';
    }

    t = "$" + t + "^";
    vi p(SIZE(t));

    int l = 0, r = 1;
    forsn(i, 1, SIZE(t)-1){
        if (i <= r) p[i] = min(r - i, p[l + r - i]);
        while (t[i - p[i]] == t[i + p[i]]) p[i]++;
        if (i + p[i] > r) l = i - p[i], r = i + p[i];
    }

    vi odd(n), even(n);
    forn(i, n){
        odd[i] = p[2 * i + 2] / 2; // Palindromo mas largo centrado en i
        even[i] = p[2 * i + 1] / 2; // Palindromo mas largo centrado en [i-1, i]
    }

    return make_pair(odd, even);
}