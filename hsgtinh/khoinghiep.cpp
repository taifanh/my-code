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

int n;
ii p[ar];
bool vs[ar];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "khoinghiep"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> p[i].fi >> p[i].se;
    sort(p + 1, p + n + 1);

    set <ii> s;
    for(int i = 1; i <= n; ++i) {
        cout << p[i].fi << ' ' << p[i].se << '\n';
        s.insert({p[i].se, -i});
    }

    int cnt = 0;
    ll res = 0;
    for(int i = 1; i <= n; ++i) if(!vs[i]) {
        if(p[i].fi <= cnt) {
            cnt++;
            vs[i] = 1;
            s.erase({p[i].se, -i});
            continue;
        }

        while(!vs[i] && p[i].fi > cnt) {
            ii j = *s.begin();
            s.erase(s.begin());

            j.se = -j.se;
            vs[j.se] = 1;
            cnt++;
            res += j.fi;
        }
        if(!vs[i]) {
            vs[i] = 1;
            cnt++;
            s.erase({p[i].se, -i});
        }
        cout << i << ' ' << res << '\n';
    }
    cout << res;
}

