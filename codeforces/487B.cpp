#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()
#define int ll


using namespace std;

typedef long long ll;

const int ar = 2e5+2;
const ll mod = 1e9+7;
const int oo = 1e9+1;
const int LG = 19;

struct RMQ_MAX {
    int rmq[ar][LG + 1];

    void update(int i, int val) {
        rmq[i][0] = val;
        for(int j = 1; j <= LG && (i - (1 << j) + 1 >= 1); ++j)
            rmq[i][j] = max(rmq[i][j - 1], rmq[i - (1 << (j - 1))][j - 1]);
    }

    int get(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return max(rmq[r][k], rmq[l + (1 << k) - 1][k]);
    }
} maxa;

struct RMQ_MIN {
    int rmq[ar][LG + 1];

    void update(int i, int val) {
        rmq[i][0] = val;
        for(int j = 1; j <= LG && (i - (1 << j) + 1 >= 1); ++j)
            rmq[i][j] = min(rmq[i][j - 1], rmq[i - (1 << (j - 1))][j - 1]);
    }

    int get(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return min(rmq[r][k], rmq[l + (1 << k) - 1][k]);
    }
} mina, mindp;

int n, s, k;

int find_dp(int i) {
    if(i < k) return oo;
    int p = i - k + 1;
    if(maxa.get(p, i) - mina.get(p, i) > s) return oo;

    int l = 1, r = p;
    while(l < r) {
        int mid = l + r >> 1;
        if(maxa.get(mid, i) - mina.get(mid, i) <= s)
            r = mid;
        else l = mid + 1;
    }
    if(l == 1) return 1;
    return mindp.get(l - 1, p - 1) + 1;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "487B"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n >> s >> k;
    for(int a, i = 1; i <= n; ++i) {
        cin >> a;
        mina.update(i, a);
        maxa.update(i, a);
        int dp = find_dp(i);
        mindp.update(i, dp);
        if(i == n) {
            if(dp >= oo) cout << -1;
            else cout << dp;
        }
    }
}

