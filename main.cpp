class CentroidDecomposition{
    public :
    vector<set<int>> tree;
    vector<int> sub;
    vector<vector<int>> ad;
    int c = -1;
    CentroidDecomposition(vector<set<int>> &tree) : tree(tree) {
        int n = tree.size();
        ad.resize(n+1);
        sub.resize(n+1);
        build(1, 0);
    }
    void build(int u, int p) {
        int n = dfs(u, p);
        int centroid = dfs(u, p, n);
        if(p == 0){
            p = centroid;
            c = p;
        }
        else{
            ad[centroid].pb(p);
            ad[p].pb(centroid);
        }
        while(!tree[centroid].empty()){
            auto v = *tree[centroid].begin();
            tree[centroid].erase(v);
            tree[v].erase(centroid);
            build(v, centroid);
        }
    }
    int dfs(int u, int p) {
        sub[u] = 1;
        for (auto v : tree[u])
            if (v != p) sub[u] += dfs(v, u);
        return sub[u];
    }
    int dfs(int u, int p, int n) {
        for (auto v : tree[u])
            if (v != p and sub[v] > n/2) return dfs(v, u, n);
        return u;
    }
};
