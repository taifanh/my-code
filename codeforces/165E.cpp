#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()

using namespace std;

typedef long long ll;

const int ar = 4e6+2;
const ll mod = 1e9+7;
const int oo = 1e9;
const int LG = 22;

int n, a[ar], f[(1 << LG) + 1];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "165E"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n;
    memset(f, -1, sizeof f);
    for(int i = 1; i <= n; ++i)
        cin >> a[i], f[a[i]] = a[i];
    for(int i = 0; i <= LG; ++i)
        for(int mask = 0; mask < (1 << LG); ++mask)
        if(mask >> i & 1) f[mask] = max(f[mask], f[mask ^ (1 << i)]);
    for(int i = 1; i <= n; ++i)
        cout << f[(1 << LG) - 1 - a[i]] << ' ';
}

