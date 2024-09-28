#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()
#define c(cs, n) (n / mu[cs])
#define p(n, cs) (n * mu[cs])


using namespace std;

typedef long long ll;

const int ar = 2e5+2;
const ll mod = 1e9+7;
const int oo = 1e9;

int n, mu[10];

int scs(int n) {
    int cnt = 0;
    while(n) cnt++, n /= 10;
    return cnt - 1;
}

int cal(int cs) {
    int m = 1, res = 0, cnt = 1;
    while(m < mu[cs]) {
        res += (cnt - 1) * 10 + 9;
        cnt++;
        m *= 10;
    }
    return res;
}

void solve() {
    cin >> n;
    if(n < 10) return cout << n - 1 << '\n', void();

    int cs = scs(n);
//    bool sub = (c(cs, n) > 1 && c(1, n) % 10 == 1);
    int res = cal(cs);
//    cout << res << '\n';
    if(n % mu[cs] == 0) {
        if(n == mu[cs]) return cout << res << '\n', void();
        if(c(cs, n) == 2) res += 10 * cs;
        else res += 10 * cs + c(cs, n) - 1;
    }
    else {
        bool ok1 = 1;
        if(c(cs, n) == 1) ok1 = 0;
        res += c(cs, n) + 1 - (c(cs, n) == 1);
        n -= p(c(cs, n), cs);
        cs = scs(n);
//        cout << res << '\n';

        bool ok = 0;
        if(cs > 0) ok = (c(cs, n) == 1);
        res += c(cs, n) - 1 + (cs > 0);
        n -= p(c(cs, n), cs);
        cs = scs(n);
//        cout << res << '\n';

        while(n) {
//            cout << c(cs, n) << ' ' << cs << '\n';
            if(cs > 0) ok |= (c(cs, n) == 1);
            res += c(cs, n) + (cs > 0);
            n -= p(c(cs, n), cs);
            cs = scs(n);
        }
        res -= (ok & ok1);
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "NUMBER"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    mu[0] = 1;
    for(int i = 1; i <= 9; ++i)
        mu[i] = mu[i - 1] * 10;
    int t;
    cin >> t;
    while(t--) solve();
}

