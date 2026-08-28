void dfs2(int v, int acc, bool keep)
{
    for_adj(c, u, v) if (u != hch[v]) dfs2(u, acc ^ (1 << c), 0);
    if (hch[v]) dfs2(hch[v], acc ^ (1 << hchc[v]), 1);
    
    cur_dep = dep[v];
    insert(acc, dep[v]);
    for_adj(c, u, v) if (u != hch[v])
        contribute(u, acc ^ (1 << c), ans[v]),
        insert_subtree(u, acc ^ (1 << c));
    if (m[acc])
        chmax(ans[v], m[acc] - cur_dep);
    forn(i, 22) {
        int x = m[acc ^ (1 << i)];
        if (x)
            chmax(ans[v], x - cur_dep);
    }
    if (not keep) clear(v, acc);
}