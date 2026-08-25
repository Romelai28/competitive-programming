cin >> s;
n = s.size();
s = s + s;
int i = 0, j = 1, k = 0;

while (i < n and j < n and k < n)
    if (i == j) i++;
    else if (s[i + k] == s[j + k])
        k++;
    else if (s[i + k] < s[j + k])
        j = j + k + 1,
        k = 0;
    else
        i = i + k + 1,
        k = 0;
        
cout << s.substr(min(i, j), n);
// O(n) rotacion mas chica lexicografica