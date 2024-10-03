#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()

using namespace std;

typedef long long ll;

const int ar = 1e6+2;
const ll mod = 1e9+7;
const int oo = 1e9;
const int S = 450;

struct Query {
    int l, r, i;
};
bool operator < (Query a, Query b) {
    return make_pair(a.l / S,  (a.l / S & 1) ? -a.r : a.r) < make_pair(b.l / S,  (b.l / S & 1) ? -b.r : b.r);
}
vector <Query> query;

int n, q, a[ar];
ll ans = 0, res[ar];
ll cnt[ar];

void add(int i) {
    i = a[i];
    cnt[i]++;
    ans += (cnt[i] * cnt[i] - (cnt[i] - 1) * (cnt[i] - 1)) * i;
}

void sub(int i) {
    i = a[i];
    ans -= (cnt[i] * cnt[i] - (cnt[i] - 1) * (cnt[i] - 1)) * i;
    cnt[i]--;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "86D"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n >> q;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];
    for(int i = 1; i <= q; ++i) {
        int l, r;
        cin >> l >> r;
        query.push_back({l, r, i});
    }
    sort(all(query));

    int L = 1, R = 0;
    for(auto [l, r, i] : query) {
        while(L > l) add(--L);
        while(R < r) add(++R);
        while(L < l) sub(L++);
        while(R > r) sub(R--);
        res[i] = ans;
    }
    for(int i = 1; i <= q; ++i)
        cout << res[i] << '\n';
}
