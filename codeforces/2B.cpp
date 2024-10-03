#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()
#define ii pair <int, int>
#define x first
#define y second

using namespace std;

typedef long long ll;

const int ar = 1000+2;
const ll mod = 1e9+7;
const int oo = 1e9;
const int N5 = 15;

int n, a[ar][ar], dp[ar][ar][2];
int trace[ar][ar];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "2B"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
        cin >> a[i][j];
    memset(dp, 0x3f, sizeof dp);
    dp[1][0][0] = dp[0][1][0] = dp[0][1][1] = dp[1][0][1] = 0;
    for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j) {
        int x = a[i][j];
        dp[i][j][0] = dp[i][j][1] = 0;
        while(x % 5 == 0) dp[i][j][1]++, x /= 5;
        while(x % 2 == 0) dp[i][j][0]++, x /= 2;
        for(int t = 0; t < 2; ++t) {
            if(dp[i - 1][j][t] < dp[i][j - 1][t])
                dp[i][j][t] += dp[i - 1][j][t], trace[i][j] = 0;
            else dp[i][j][t] += dp[i][j - 1][t], trace[i][j] = 1;
        }
    }

    int res = oo;
    ii pos;
    for(int t = 0; t < 2; ++t)
        if(res > dp[n][n][t])
            res = dp[n][n][t], pos = {n, n};
    cout << res << '\n';
    vector <char> duong;
    while(pos.x && pos.y) {
        if(trace[pos.x][pos.y]) {
            pos.y--;
            duong.push_back('R');
        }
        else {
            pos.x--;
            duong.push_back('D');
        }
    }
    duong.pop_back();
    reverse(all(duong));
    for(auto x : duong)
        cout << x;
}
