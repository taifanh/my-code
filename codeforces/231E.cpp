#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()
#define ii pair <int, int>
#define fi first
#define se second

using namespace std;

typedef long long ll;

const int ar = 2e5+2;
const ll mod = 1e9+7;
const int oo = 1e9;

int n, m;
int timeDfs = 0, scc = 0;
int low[ar], num[ar];
int id[ar], pos[ar];
bool deleted[ar], vs[ar];
vector <int> g[ar], tplt[ar], adj[ar];
stack <int> st;

void dfs(int u, int p) {
    num[u] = low[u] = ++timeDfs;
    st.push(u);
    for (int v : g[u]) if(v != p) {
      if (deleted[v]) continue;
        if (!num[v]){
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        }
        else low[u] = min(low[u], num[v]);
    }
    if (low[u] == num[u]) {
        scc++;
        int v;
        do {
            v = st.top();
            st.pop();
            tplt[scc].push_back(v);
            id[v] = scc;
            pos[v] = tplt[scc].size();
            deleted[v] = true;
        }
        while (v != u);
    }
}

int h[ar], up[ar][18];
ll dp[ar][18];

inline int mul(ll a, int b) {
    a *= b;
    if(a >= mod) a %= mod;
    return a;
}

int cal(int u, int v) {
    return min(abs(pos[u] - pos[v]), int(tplt[id[u]].size()) - abs(pos[u] - pos[v]));
}

void dfs2(int u, int p) {
    int goc = u;
    int s = id[u];
    for(auto u : tplt[s]) {
        for(int j = 0; j < 17; ++j)
            dp[u][j] = dp[goc][j];
        for(auto v : g[u]) if(id[v] != s && v != p){
            h[id[v]] = h[s] + 1;
            up[id[v]][0] = u;
            dp[v][0] = (tplt[id[v]].size() > 1) + 1;
            for(int j = 1; j < 17; ++j) {
                up[id[v]][j] = up[id[up[id[v]][j - 1]]][j - 1];
                dp[v][j] = mul(dp[up[id[v]][j - 1]][j - 1], dp[v][j - 1]);
            }
//            cout << u << ' ' << v << ' ' << dp[v][0] << '\n';
            dfs2(v, u);
        }
    }
}

int lca(int u, int v) {
    ll res = 1;
    if(h[id[u]] != h[id[v]]) {
        if(h[id[u]] < h[id[v]]) swap(u, v);

        int k = h[id[u]] - h[id[v]];
        for(int j = 0; (1 << j) <= k; ++j)
            if(k >> j & 1)  {
                res *= dp[u][j];
                res %= mod;
                u = up[id[u]][j];
            }
    }
    if(id[u] == id[v]) {
        if(tplt[id[u]].size() > 1) res *= 2, res %= mod;
        return res;
    }

    int k = 31 - __builtin_clz(h[id[u]]);
    for(int j = k; j >= 0; --j)
    if(id[up[id[u]][j]] != id[up[id[v]][j]]) {
        res *= mul(dp[u][j], dp[v][j]);
        res %= mod;
        u = up[id[u]][j];
        v = up[id[v]][j];
    }
    res *= mul(dp[u][0], dp[v][0]);
    res %= mod;
    u = up[id[u]][0]; v = up[id[v]][0];
    if(tplt[id[u]].size() > 1) res *= 2, res %= mod;
    return res;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "x"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n >> m;
    int u, v;
    for(int i = 1; i <= m; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
//    for(int i = 1; i <= scc; ++i) {
//        for(auto u : tplt[i]) cout << u << ' ';
//        cout << '\n';
//    }
    dfs2(1, 0);
    int q;
    cin >> q;
    while(q--) {
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
}

