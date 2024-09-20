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

int n, cnt[ar], a[ar], L, R;
ll res = 0;
vector <ll> f, g;

void add(int x) {
    x = a[x];
    res += cnt[x];
    cnt[x]++;
}

void del(int x) {
    x = a[x];
    cnt[x]--;
    res -= cnt[x];
}

ll cost(int l, int r) {
    while(L > l) add(--L);
    while(R < r) add(++R);
    while(L < l) del(L++);
    while(R > r) del(R--);
    return res;
}

void dnc(int l, int r, int optl, int optr) {
    if(l > r) return;

    int mid = l + r >> 1;
    pair <ll, int> opt = {g[optl - 1] + cost(optl, mid), optl};
    for(int i = optl + 1; i <= min(optr, mid); ++i)
        opt = min(opt, {g[i - 1] + cost(i, mid), i});
    f[mid] = opt.fi;
    dnc(l, mid - 1, optl, opt.se);
    dnc(mid + 1, r, opt.se, optr);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "868F"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    int k;
    cin >> n >> k;
    f.resize(n + 1, 0);
    g.resize(n + 1, 0);
    L = 1, R = n;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        res += cnt[a[i]];
        g[i] = res;
        cnt[a[i]]++;
    }
    --k;
    while(k--) {
        dnc(1, n, 1, n);
        g = f;
    }
    cout << f[n];
}

