#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()

using namespace std;

typedef long long ll;

const int ar = 2e5+2;
const ll mod = 1e9+7;
const int oo = 1e9;
const int LG = 18;

int n, m, q, a;
int pos[ar], rmq[ar][LG + 1], nxt[ar][LG + 1], lst[ar], near[ar];

int jump(int i, int k) {
    if(i <= 0) return 0;
    for(int j = LG; j >= 0; --j)
        if(k & (1 << j))
            i = nxt[i][j];
    return i;
}

int get(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return max(rmq[r][k], rmq[l + (1 << k) - 1][k]);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "1142B"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n >> m >> q;
    for(int i = 1; i <= n; ++i) {
        cin >> a;
        pos[a] = i;
    }
    vector <int> vitri;
    for(int i = 1; i <= m; ++i) {
        cin >> a;
        a = pos[a];
        int p = i;
        if(a > 1) {
            p = lst[a - 1];
            p = near[p];
        }
        near[i] = p;
        if(a == n) vitri.push_back(i);
        else {
            p = lb(vitri, p) - 1;
            if(p >= 0) p = vitri[p];
            p = jump(p, n - a - 1);
        }

        rmq[i][0] = p;
        for(int j = 1; j <= LG && (i - (1 << j) + 1) > 0; ++j)
            rmq[i][j] = max(rmq[i][j - 1], rmq[i - (1 << (j - 1))][j - 1]);

        nxt[i][0] = lst[a - 1];
        for(int j = 1; j <= LG; ++j)
            nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
        lst[a] = i;
    }

    while(q--) {
        int l, r;
        cin >> l >> r;
        if(get(l, r) >= l) cout << 1;
        else cout << 0;
    }
}

