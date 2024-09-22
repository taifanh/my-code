#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()
#define ii pair <ll, int>
#define fi first
#define se second

using namespace std;

typedef long long ll;

const int ar = 2e5 + 2;
const ll mod = 1e9 + 7;
const int oo = 1e9;

int n;
ll a[ar];

void solve() {
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];

    stack <ii> s;
    for(int i = 1; i <= n; i++) {
        ll sum = a[i], cnt = 1;
        while(s.size() && s.top().fi >= sum / cnt) {
            sum += s.top().fi * s.top().se;
            cnt += s.top().se;
            s.pop();
        }
        s.push({sum / cnt, cnt - sum % cnt});
        if(sum % cnt != 0) {
            s.push({sum / cnt + 1, sum % cnt});
        }
    }
    ll mx = s.top().fi;
    while(s.size() > 1) {
        s.pop();
    }
    cout << mx - s.top().fi << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
#define task "2013D"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    int t;
    cin >> t;
    while(t--) solve();
}

