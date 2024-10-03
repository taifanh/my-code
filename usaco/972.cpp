#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()

using namespace std;

typedef long long ll;

const int ar = 302;
const ll mod = 1e9+7;
const int oo = 1e9;

void maxi(int &a, int b) {
    if(a < b) a = b;
}

int n, m, mx[ar][ar][ar], dp[ar][ar];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "pieaters"
    if(fopen(task".in", "r")) {
        freopen(task".in", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n >> m;
    while(m--) {
        int l, r, w;
        cin >> w >> l >> r;
        for(int i = l; i <= r; ++i)
            maxi(mx[i][l][r], w);
    }

    for(int i = n; i >= 1; --i)
        for(int j = i; j <= n; ++j)
        for(int k = i; k <= j; ++k)
        maxi(mx[k][i][j], max(mx[k][i + 1][j], mx[k][i][j - 1]));

    for(int i = n; i >= 1; --i)
    for(int j = i; j <= n; ++j) {
        for(int k = i + 1; k <= j; ++k)
            maxi(dp[i][j], dp[i][k - 1] + dp[k][j]);
        for(int k = i; k <= j; ++k) {
            int res = mx[k][i][j];
            if(k > i) res += dp[i][k - 1];
            if(k < j) res += dp[k + 1][j];
            maxi(dp[i][j], res);
        }
    }
    cout << dp[1][n];
}

