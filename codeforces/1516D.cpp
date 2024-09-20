#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()

using namespace std;

typedef long long ll;

const int ar = 2e5+2;
const ll mod = 1e9+7;
const int oo = 1e9;
const int LG = 17;
const int N = 1e5;

int n, q, nxt[ar][LG + 1], rmq[ar][LG + 1];
int nt[ar], lst[ar];

int getMax(int l, int r) {
    if(l > r) return 0;
    int k = 31 - __builtin_clz(r - l + 1);
    return max(rmq[r][k], rmq[l + (1 << k) - 1][k]);
}

int cal(int l, int r) {
    int res = 0;
    for(int i = LG; i >= 0; --i) {
        if(nxt[r][i] < l) continue;
        res += (1 << i);
        r = nxt[r][i];
    }
    return res + 1;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "1516D"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    iota(nt + 1, nt + N + 1, 1);
    for(int i = 2; i * i <= N; ++i)
        if(nt[i] == i)
        for(int j = i * i; j <= N; j += i)
            nt[j] = i;
    cin >> n >> q;
    for(int a, i = 1; i <= n; ++i) {
        cin >> a;
        while(a > 1) {
            int x = nt[a];
            nxt[i][0] = max(nxt[i][0], lst[x]);
            lst[x] = i;
            while(a % x == 0) a /= x;
        }
        nxt[i][0] = rmq[i][0] = max(nxt[i][0], getMax(nxt[i][0] + 1, i - 1));
        for(int j = 1; j <= LG; ++j)
            nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
        for(int j = 1; j <= LG; ++j)
            rmq[i][j] = max(rmq[i][j - 1], rmq[rmq[i][j - 1]][j - 1]);
//        cout << nxt[i][0] << ' ';
    }

    while(q--) {
        int l, r;
        cin >> l >> r;
        cout << cal(l, r) << '\n';
    }
}

