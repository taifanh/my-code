#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()

using namespace std;

typedef long long ll;

const int ar = 2e5+2;
const ll mod = 1e9+7;
const int oo = 1e9;

ll n, m, u, v, x, ans, e[24][24], f[1 << 19][24];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "11D"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        cin >> u >> v;
        --u; --v;
        e[u][v] = e[v][u] = 1;
    }
    for(int i = 0; i < n; ++i)
        f[1 << i][i] = 1;

    for(int mask = 1; mask < (1 << n); ++mask)
    for(int i = 0; i < n; ++i)
    if(f[mask][i]) for(int j = 0; j < n; ++j) {
        x = 1 << j;
        if(e[i][j] && x >= (mask & -mask)) {
            if(mask & x)
                 ans += !(x ^ mask & -mask) * f[mask][i];
            else f[mask | x][j] += f[mask][i];
        }
    }
    cout << (ans - m) / 2;
}
