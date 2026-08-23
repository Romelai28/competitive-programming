class AhoCorasickAutomaton
{
    const int nil = -1;
    vi freq = { 0 };
    vi fail = { 0 };
    vector<vi> children = { vi(26, nil) };
    vi end_nodes;
    int size() { return children.size(); }
    int make_node() {
        int n = size();
        freq.push_back(0);
        fail.push_back(0);
        children.emplace_back(26, nil);
        return n;
    }
    int get_child(int n, char x) {
        if (children[n][x - 'a'] != nil) return children[n][x - 'a'];
        return children[n][x - 'a'] = make_node();
    }
    int dfs(const vector<vi>& G, int v) {
        for (int w : G[v])
            freq[v] += dfs(G, w);
        return freq[v];
    }
public:
    int insert(const string& s) {
        int n = 0;
        for (char x : s) n = get_child(n, x);
        end_nodes.push_back(n);
        return n;
    }
    void set_fail() {
        vi que;
        for (int i = 0; i < 26; ++i)
        if (children[0][i] == nil)
            children[0][i] = 0;
        else
            fail[children[0][i]] = 0,
            que.push_back(children[0][i]);
        while (not que.empty())
        {
            vi ext;
            for (int n : que)
            for (int i = 0; i < 26; ++i)
            if (children[n][i] == nil)
                children[n][i] = children[fail[n]][i];
            else
                fail[children[n][i]] = children[fail[n]][i],
                ext.push_back(children[n][i]);
            swap(ext, que);
        }
    }
    void read(const string& text) {
        int n = 0;
        for (char x : text) n = children[n][x - 'a'], freq[n]++;
    }
    void bake() {
        vector<vi> G(size());
        for (int n = 1; n < size(); ++n)
            G[fail[n]].push_back(n);
        dfs(G, 0);
    }
    vi get_frequencies() {
        vi ans;
        for (int n : end_nodes) ans.push_back(freq[n]);
        return ans;
    }
}; // Complejidad O(|t1|+...+|tk|+|s|)
 
int n, k;
string s, t;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> s;
    n = s.size();
    cin >> k;
    AhoCorasickAutomaton A;
    for (int _ = 0; _ < k; ++_) {
        cin >> t;
        A.insert(t);
    }
    
    A.set_fail();
    A.read(s);
    A.bake();
    
    for (int x : A.get_frequencies()) cout << x << '\n';
}