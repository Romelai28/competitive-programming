vi end_nodes = { -1 };
int fail[MAXN];
int word[MAXN];
int children[MAXN][26];
struct AhoCorasickAutomaton
{
    static const int nil = 0;
    int node_count = 1;
    
    int make_node() {
        return node_count++;
    }
    
    int get_child(int n, char x) {
        if (children[n][x - 'a'] != nil) children[n][x - 'a'];
        else return children[n][x - 'a'] = make_node();
    }
    
    void insert(const string& s) {
        stack<int, vi> stk;
        int n = 0;
        for (char x : s)
            if (x == 'P')
                word[n] = end_nodes.size(),
                end_nodes.push_back(n);
            else if (x == 'B')
                n = stk.top(), stk.pop();
            else
            {
                stk.push(n);
                n = get_child(n, x);
            }
    }
    
    void set_fail() {
        vi que;
        forn(i, 26)
        if (children[0][i] == nil)
            children[0][i] = 0;
        else 
            fail[children[0][i]] = 0,
            que.push_back(children[0][i]);
        
        while (not que.empty())
        {
            vi ext;
            for (int n : que)
                forn(i, 26)
                if (children[n][i] == nil)
                    children[n][i] = children[fail[n]][i];
                else
                    fail[children[n][i]] = children[fail[n]][i],
                    ext.push_back(children[n][i]);
            swap(ext, que);
        }
    }
    
    vector<vi> get_fail_tree() {
        vector<vi> T(node_count);
        for (int n = 1; n < node_count; ++n)
            T[fail[n]].push_back(n);
        return T;
    }
} A;


int dfn[MAXN], sz[MAXN];
int ts = 1;
int dfs(const vector<vi>& T, int v) {
    dfn[v] = ts++;
    sz[v] = 1;
    for (int w : T[v]) sz[v] += dfs(T, w);
    return sz[v];
}

#define lowbit(x) ((x) & -(x))
ll t[MAXN];
int tree_size;

void add(int i, ll x) {
    while (i <= tree_size) t[i] += x, i += lowbit(i);
}

ll query(int i) {
    ll ans = 0;
    while (i) ans += t[i], i -= lowbit(i);
    return ans;
}


vector<ii> queries[MAXN];
ll ans[MAXN];
string s;


void solve()
{
    stack<int, vi> stk;
    int n = 0;
    for (char x : s)
        if (x == 'B')
        {
            add(dfn[n], -1);
            n = stk.top(), stk.pop();
        }
        else if (x == 'P')
            for (auto&& [x, iq] : queries[word[n]])
            {
                int nx = end_nodes[x];
                ans[iq] = query(dfn[nx] + sz[nx] - 1)
                    - query(dfn[nx] - 1);
            }
        else
        {
            stk.push(n);
            n = children[n][x - 'a'];
            add(dfn[n], 1);
        }
}