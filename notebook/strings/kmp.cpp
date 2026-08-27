// PI_S[i] := max{k | 1<=k<i and S[0:k-1] = S[i-(k-1):i]}
vi prefix_function_kmp(const string &s) {
	int n = SIZE(s); vi pi_s(n);
	for (int i=1, j=0; i<n; i++) {
		while (j > 0 && s[j] != s[i]) { j = pi_s[j - 1]; }
		if (s[i] == s[j]) { j++; }
		pi_s[i] = j;
	}
	return pi_s;
}
// Alternativa: usar kmp sobre p + '#' + s.
int matching_kmp(const string &text, const string &pattern){
	int n = SIZE(text), m = SIZE(pattern), len = 0, times = 0; // Contador de apariciones del patron
	vi lps = prefix_function_kmp(pattern);
	forn(i, n){
		while (len > 0 && pattern[len] != text[i]) { len = lps[len-1]; }
		if (pattern[len] == text[i]) { len++; }
		if (len == m) {
			times++;  // Patron esta en s[i-m+1 : i] (text.substr(i-m+1, m) == pattern)
			len = lps[len-1];
		}
	}
	return times;
}