int lcs(vi a, vi b) { // Longest Common Subsequence
   vvi m(2, vi(b.size()+1));
	forn(i,a.size())forn(j,b.size())
		m[1-i %2][j+1]=(a[i]==b[j]?m[i %2][j]+1:max(m[i %2][j+1],m[1-i %2][j]));
	return m[a.size() %2][b.size()];
}