#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()

using namespace std;

typedef long long ll;

const int ar = 2e5+2;
const ll mod = 1e9+7;
const int oo = 1e9;

int n, a[ar], rmq[ar][21], suf[ar];

int get(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return min(rmq[l][k], rmq[r - (1 << k) + 1][k]);
}
    map <int, int> mp;

void solve() {
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        rmq[i][0] = a[i];
    }
    for(int j = 1; j <= 19; ++j)
        for(int i = 1; i + (1 << j) - 1 <= n; ++i)
        rmq[i][j] = min(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j - 1]);
    suf[n + 1] = 0;
    mp.clear();
    for(int i = n; i >= 1; --i) {
        suf[i] = max(suf[i + 1], a[i]);
        if(!mp[a[i]]) mp[a[i]] = i;
    }

    int pre = 0;
    for(int i = 1; i <= n - 2; ++i) {
        pre = max(pre, a[i]);
        if(i >= mp[pre]) continue;
        int l = i + 1, r = mp[pre] - 1;
        if(l > r) continue;
        while(l < r) {
            int mid = l + r + 1 >> 1;
            if(get(i + 1, mid) >= pre)
                l = mid;
            else r = mid - 1;
        }
//        cout << i << ' ' << l << ' ' << r << '\n';
        if(get(i + 1, r) == pre && suf[r + 1] == pre) {
            cout << "YES\n";
            cout << i << ' ' << r - i << ' ' << n - r << '\n';
            return;
        }
    }
    cout << "NO\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "1454F"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    int t;
    cin >> t;
    while(t--) solve();
}

