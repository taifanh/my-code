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
const int LG = 19;

int n, a[ar];
ll dp[ar];
ii rmq[ar][LG + 1];

void update(int i, int val) {
    rmq[i][0] = {val, i};
    for(int j = 1; j <= LG && (i + (1 << j) - 1 <= n); ++j)
        rmq[i][j] = max(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j - 1]);
}

ii get(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return max(rmq[l][k], rmq[r - (1 << k) + 1][k]);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "675E"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n;
    n--;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];
    dp[n] = 1;
    update(n, a[n]);
    ll res = 1;
    for(int i = n - 1; i >= 1; --i) {
        int j = get(i + 1, min(n, a[i])).se;
//        cout << i << ' ' << j << '\n';
        dp[i] = dp[j] + n - i + 1 - (a[i] - j);
        res += dp[i];
        update(i, a[i]);
    }
    cout << res;
}

