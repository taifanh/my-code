#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()

using namespace std;

typedef long long ll;

const int ar = 2e5+2;
const ll mod = 1e9+7;
const int oo = 1e9;

int n, c[ar];
vector <int> g[ar];
int sz[ar];
int in[ar], out[ar], timeDfs = 0, node[ar];
ll ans = 0, res[ar];
int cnt[ar];
int mx = 0;

void precal(int u, int p) {
    in[u] = ++timeDfs;
    node[timeDfs] = u;
    sz[u] = 1;
    for(auto v : g[u]) if(v != p) {
        precal(v, u);
        sz[u] += sz[v];
    }
    out[u] = timeDfs;
}

void del(int u) {
    ans = 0;
    mx = 0;
    for(int i = in[u]; i <= out[u]; ++i)
        cnt[c[node[i]]]--;
}

void add(int l, int r) {
    for(int i = l; i <= r; ++i) {
        int v = node[i];
        cnt[c[v]]++;
        if(cnt[c[v]] == mx)
            ans += c[v];
        else if(cnt[c[v]] > mx)
            ans = c[v], mx = cnt[c[v]];
    }
}

void dfs(int u, int p) {
    int big = 0;
    for(int v : g[u]) if(v != p && sz[v] > sz[big])
        big = v;
    for(int v : g[u]) {
        if(v == big || v == p) continue;
        dfs(v, u);
        del(v);
    }
    if(big != 0)
        dfs(big, u);
    add(in[u], in[u]);
    for(int v : g[u]) {
        if(v == big || v == p) continue;
        add(in[v], out[v]);
    }
    res[u] = ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "600"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> c[i];
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    sz[0] = -1;
    precal(1, 0);
    dfs(1, 0);
    for(int i = 1; i <= n; ++i)
        cout << res[i] << ' ';
}

