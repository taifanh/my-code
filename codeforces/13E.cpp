#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()

using namespace std;

typedef long long ll;

const int ar = 2e5+2;
const ll mod = 1e9+7;
const int oo = 1e9;
const int BLOCK = 450;

int n, m, a[ar];
int ans[ar], lst[ar];

void update(int bl) {
    int l = max(1, bl * BLOCK), r = min(n, (bl + 1) * BLOCK - 1);
    for(int i = r; i >= l; --i)
        if(i + a[i] > r) ans[i] = 1, lst[i] = i;
        else ans[i] = ans[i + a[i]] + 1, lst[i] = lst[i + a[i]];
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "13E"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];
    for(int i = 1; i <= n; ++i)
        update(i / BLOCK);

    int t, i, v;
    while(m--) {
        cin >> t >> i;
        if(t == 0) {
            cin >> v;
            a[i] = v;
            update(i / BLOCK);
        }
        else {
            int res = 0, l = i;
            while(i <= n) {
                res += ans[i];
                i = lst[i];
                l = lst[i];
                i += a[i];
            }
            cout << l << ' ' << res << '\n';
        }
    }
}

