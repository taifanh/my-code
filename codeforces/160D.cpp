#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()
#define ii pair <int, int>
#define fi first
#define se second

using namespace std;

typedef long long ll;

const int M = 2e5+5;
const int N = 2e5+5;
const ll mod = 1e9+7;
const int oo = 1e9;

struct Edge {
    int u, v, c, i;
};

struct Node {
    int v, c, i;
};

struct Dsu {
    vector<int> par;

    void init(int n) {
        par.resize(n + 5, 0);
        for (int i = 1; i <= n; i++) par[i] = i;
    }

    int find(int u) {
        if (par[u] == u) return u;
        return par[u] = find(par[u]);
    }

    bool join(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return false;
        par[v] = u;
        return true;
    }
} dsu;

int n, m;
vector < Edge > edges;
vector <Node> g[N], adj[N];
bool choose[M];

int h[N], up[N][20], ma[N][20];
ii lca(int u, int v) {
    int res = 0;
    if (h[u] != h[v]) {
        if (h[u] < h[v]) swap(u, v);

        int k = h[u] - h[v];
        for (int j = 0; (1 << j) <= k; ++j)
            if (k >> j & 1)
                res = max(res, ma[u][j]), u = up[u][j];
    }
    if (u == v) return {u, res};

    int k = 31 - __builtin_clz(h[u]);
    for (int j = k; j >= 0; --j)
        if (up[u][j] != up[v][j]) {
            res = max({res, ma[u][j], ma[v][j]});
            u = up[u][j], v = up[v][j];
        }
    return {up[u][0], max({res, ma[u][0], ma[v][0]})};
}

multiset <int> sz[N];
int lab[N], num[N], tf = 0, res[M];
vector <int> canh[N];

int find_set(int v) {
    return lab[v] < 0 ? v : lab[v] = find_set(lab[v]);
}

void union_sets(int a, int b, int c, int w) {
    a = find_set(a);
    b = find_set(b);

    if (a != b) {
        if(sz[b].size()) {
            res[c] = *sz[b].begin();
            if(res[c] == w) res[c] = 1;
            else res[c] = 2;
        }
        if (sz[a].size() < sz[b].size()) swap(a, b);
        for(auto x : sz[b])
            sz[a].insert(x);
        sz[b].clear();
        lab[a] += lab[b];
        lab[b] = a;
    }
}

void prepare(int u) {
    for (auto [v, c, i] : g[u]) {
        if (v == up[u][0]) continue;
        h[v] = h[u] + 1;

        up[v][0] = u;
        ma[v][0] = c;
        for (int j = 1; j < 20; ++j)
            up[v][j] = up[up[v][j - 1]][j - 1],
            ma[v][j] = max(ma[v][j - 1], ma[up[v][j - 1]][j - 1]);

        prepare(v);
    }
}

void dfs(int u) {
    for (auto [v, c, i] : g[u]) {
        if (v == up[u][0]) continue;
        dfs(v);
//        int tmp = find_set(v);
//        cout << u << ' ' << v << ' ' << i << ' ' << tmp << " thu\n";
//        for(auto x : sz[tmp])
//            cout << x << ' '; cout << '\n';
        union_sets(u, v, i, c);
    }
    int tmp = find_set(u);
    for(auto [v, c, i] : adj[u]) {
        int cha = lca(u, v).fi;
        if(cha != u) {
            sz[tmp].insert(c);
            canh[cha].push_back(c);
        }
    }
    for(auto c : canh[u])
        sz[tmp].erase(sz[tmp].find(c));
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "160D"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n >> m;
    memset(lab, -1, sizeof lab);
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        edges.push_back({u, v, c, i});
        res[i] = 2;
    }

    dsu.init(n);

    sort(edges.begin(), edges.end(), [](Edge & x, Edge & y) {
        return x.c < y.c;
    });

    int maxc = 0;
    for (auto [u, v, c, i] : edges) {
        if (!dsu.join(u, v)) {
            maxc = max(maxc, c);
            adj[u].push_back({v, c, i});
            adj[v].push_back({u, c, i});
            continue;
        }
//        cout << u << ' ' << v << ' ' << c << '\n';
        choose[i] = 1;
        g[u].push_back({v, c, i});
        g[v].push_back({u, c, i});
    }

    prepare(1);
    dfs(1);
    for(auto [u, v, c, i] : edges) if(!choose[i]) {
        ii tmp = lca(u, v);
//        cout << u << ' ' << v << ' ' << tmp.fi << ' ' << tmp.se << '\n';
        if(tmp.se < c) res[i] = 0;
        else res[i] = 1;
    }
    for(int i = 1; i <= m; ++i) {
//        cout << res[i] << ' ';
        if(res[i] == 2) cout << "any";
        else if(res[i] == 0) cout << "none";
        else cout << "at least one";
        cout << '\n';
    }
}
