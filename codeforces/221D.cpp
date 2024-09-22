#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()

using namespace std;

typedef long long ll;

const int ar = 2e5+2;
const ll mod = 1e9+7;
const int oo = 1e9;
const int S = 320;

struct Query {
    int l, r, i;
};
bool operator < (Query a, Query b) {
    if(a.l / S != b.l / S)
        return a.l < b.l;
        return a.r < b.r;
}
vector <Query> query;

int n, m, a[ar];
int cnt[ar], ans = 0, res[ar];

void add(int x) {
    x = a[x];
    if(x > n) return;
    if(cnt[x] == x) ans--;
    cnt[x]++;
    if(cnt[x] == x) ans++;
}

void sub(int x) {
    x = a[x];
    if(x > n) return;
    if(cnt[x] == x) ans--;
    cnt[x]--;
    if(cnt[x] == x) ans++;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "221D"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];
    for(int i = 1; i <= m; ++i) {
        int l, r;
        cin >> l >> r;
        query.push_back({l, r, i});
    }
    sort(all(query));

    int L = 1, R = 0;
    for(auto [l, r, j] : query) {
        while(L > l) add(--L);
        while(R < r) add(++R);
        while(L < l) sub(L++);
        while(R > r) sub(R--);
        res[j] = ans;
    }
    for(int i = 1; i <= m; ++i)
        cout << res[i] << '\n';
}

