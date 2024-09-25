#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()

using namespace std;

typedef long long ll;

const int ar = 2e5+2;
const ll mod = 1e9+7;
const int oo = 1e9;

int n, a[ar];
vector <int> pos[ar];
vector <pair <int, int>> xoa[ar];

ll sum[ar * 4];
int cnt[ar * 4], lz[ar * 4];

void build(int id, int l, int r) {
    if(l == r) {
        cnt[id] = 1;
        return;
    }

    int mid = l + r >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);

    cnt[id] = cnt[id << 1] + cnt[id << 1 | 1];
}

void down(int id) {
    for(int i = id << 1; i <= (id << 1 | 1); ++i)
        sum[i] += lz[id] * cnt[i], lz[i] += lz[id];
    lz[id] = 0;
}

void update(int id, int l, int r, int u, int v, int val) {
    if(u > v) return;
    if(l >= u && r <= v) {
        sum[id] += val * cnt[id];
        lz[id] += val;
        return;
    }

    if(lz[id]) down(id);

    int mid = l + r >> 1;
    if(mid >= u) update(id << 1, l, mid, u, v, val);
    if(mid + 1 <= v) update(id << 1 | 1, mid + 1, r, u, v, val);

    sum[id] = sum[id << 1] + sum[id << 1 | 1];
}

ll get(int id, int l, int r, int u, int v) {
    if(l >= u && r <= v) return sum[id];

    if(lz[id]) down(id);

    int mid = l + r >> 1;
    ll res = 0;
    if(mid >= u) res += get(id << 1, l, mid, u, v);
    if(mid + 1 <= v) res += get(id << 1 | 1, mid + 1, r, u, v);

    return res;
}

void del(int pos) {
    if(pos == 0) return;
    int id = 1, l = 1, r = n;
    while(l < r) {
        if(lz[id]) down(id);
        int mid = l + r >> 1;
        if(mid >= pos)
            id <<= 1, r = mid;
        else id = id << 1 | 1, l = mid + 1;
    }
    sum[id] = 0;
    cnt[id] = 0;
    while(id > 1) {
        id >>= 1;
        sum[id] = sum[id << 1] + sum[id << 1 | 1];
        cnt[id] = cnt[id << 1] + cnt[id << 1 | 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "trochoi"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n;
    for(int i = 1; i <= n; ++i) pos[i].push_back(0);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    for(int i = 1; i <= n; ++i) pos[i].push_back(n + 1);

    build(1, 1, n);

    ll res = 0;
    for(int i = 1; i <= n; ++i) {
        for(auto [l, r] : xoa[i])
            update(1, 1, n, l, r, -1);

        int p = lb(pos[a[i]], i);
        int l = pos[a[i]][p - 1] + 1;
        int r = pos[a[i]][p + 1];
        res += get(1, 1, n, l, i);
//        cout << i << ' ' << l << ' ' << i << ' ' << res << ' ' << get(1, 1, n, 1, 1) << '\n';

        del(l - 1);
//        cout << l << ' ' << i - 1 << '\n';
        update(1, 1, n, l, i - 1, 1);

        xoa[r].push_back({l, i - 1});
    }
    cout << res;
}
/*
7
1 2 3 4 3 2 5
*/
