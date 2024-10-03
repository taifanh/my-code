#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()
#define BIT(mask, i) (mask >> (i) & 1)
#define MASK(i) (1 << (i))

using namespace std;

typedef long long ll;

const int ar = 105;
const ll mod = 1e9+7;
const int oo = 1e9;
const int LG = 16;

int nt[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
int n, a[ar], dp[ar][1 << LG];

inline bool mini(int &a, int b) {
    if(a > b) {
        a = b;
        return 1;
    }
    return 0;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "453B"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    for(int i = 1; i <= n; ++i)
        for(int mask = 0; mask < MASK(LG); ++mask) {
            dp[i][mask] = dp[i - 1][mask] + abs(a[i] - 1);
            int j = 0, k = 1;
            if(BIT(mask, j) && BIT(mask, k)) {
                for(int t = 2; t <= 4; ++t)
                mini(dp[i][mask], dp[i - 1][mask ^ MASK(j) ^ MASK(k) ^ MASK(t)] + abs(a[i] - nt[j] * nt[k] * nt[t]));
            }
            for(int j = 0; j < 10; ++j) if(BIT(mask, j))
                for(int k = 0; k < 10; ++k) if(BIT(mask, k))
                    if(nt[j] * nt[k] >= 59) break;
                    else mini(dp[i][mask], dp[i - 1][mask ^ MASK(j) ^ MASK(k)] + abs(a[i] - nt[j] * nt[k]));
            for(int j = 0; j < LG; ++j) if(BIT(mask, j))
                mini(dp[i][mask], dp[i - 1][mask ^ MASK(j)] + abs(a[i] - nt[j]));
            bitset <3> bit(mask);
//            cout << i << ' ' << bit << ' ' << dp[i][mask] << '\n';
        }
    cout << (*min_element(dp[n], dp[n] + MASK(LG)));
}

