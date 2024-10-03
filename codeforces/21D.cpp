#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int ar = 2000+2;
const ll mod = 1e9+7;
const int oo = 1e9;

int n, m, x[ar], y[ar], w[ar], dp[1 << 15], tmp[1 << 15];
vector <int> g[ar];
bool vs[ar];

void dfs(int u) {
    vs[u] = 1;
    for(auto v : g[u]) if(!vs[v])
        dfs(v);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "a"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n >> m;
    if(m == 0) cout << 0, exit(0);
    int mask = 0, tmp = 0;
    for(int i = 1; i <= m; ++i) {
        cin >> x[i] >> y[i] >> w[i];
        x[i]--;
        y[i]--;
        g[x[i]].push_back(y[i]);
        g[y[i]].push_back(x[i]);
        mask ^= (1 << x[i]) ^ (1 << y[i]);
        tmp += w[i];
    }
    dfs(0);
    for(int i = 0; i < n; ++i)
        if(!vs[i] && g[i].size()) cout << -1, exit(0);
    memset(dp, 0x3f, sizeof dp);
    dp[mask] = tmp;
    for(int i = 1; i <= m; ++i) {
        for(int mask = 0; mask < (1 << n); ++mask) {
            int nmask = mask;
            nmask ^= (1 << x[i]);
            nmask ^= (1 << y[i]);
            dp[nmask] = min(dp[nmask], dp[mask] + w[i]);
        }
    }
    int res = dp[0];
//    for(int i = 0; i < n; ++i)
//        for(int j = i + 1; j < n; ++j)
//        res = min(res, dp[(1 << i) | (1 << j)] * 2);
    cout << res;
}
