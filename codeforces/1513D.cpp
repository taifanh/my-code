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
const int LG = 18;

int n, p, a[ar], rmq[ar][LG + 1];

int get(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return min(rmq[l][k], rmq[r - (1 << k) + 1][k]);
}

int lab[ar];

int find_set(int u) {
    return lab[u] < 0 ? u : lab[u] = find_set(lab[u]);
}

bool union_sets(int u, int v) {
    u = find_set(u);
    v = find_set(v);
    if(u != v) {
        if(lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return 1;
    }
    return 0;
}

struct Edge {
    int u, v, c;
};
bool operator < (Edge a,Edge b) {
    return a.c < b.c;
}

vector <Edge> xuly() {
    for(int i = 1; i <= n; ++i) rmq[i][0] = a[i];
    for(int j = 1; j <= LG; ++j)
        for(int i = 1; i + (1 << j) - 1 <= n; ++i) {
            rmq[i][j] = min(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j - 1]);
//            cout << i << ' ' << i + (1 << j) - 1 << ' ' << rmq[i][j] << '\n';
        }

    vector <ii> st;
    vector <Edge> edge;
    for(int i = 1; i <= n; ++i) {
        lab[i] = -1;
        ii tmp = {a[i], i};
        vector <ii> nst;
        for(int i = st.size() - 1; i >= 0; --i) {
            if(st[i].fi == tmp.fi) {
                tmp.se = st[i].se;
                continue;
            }
            nst.push_back(tmp);
            tmp = {__gcd(tmp.fi, st[i].fi), st[i].se};
        }
        nst.push_back(tmp);
        st = nst;
//        cout << i << '\n';
//        for(auto [x, y] : st) cout << x << ' ' << y << '\n';
        reverse(all(st));
        st.push_back({0, i});
        for(int j = 0; j < st.size() - 1; ++j) {
//            cout <<
            if(st[j].fi > p || st[j].se == i) continue;
            int l = st[j].se, r = st[j + 1].se - 1;
//            cout << i << ' ' << l << ' ' << r << ' ' << st[j].fi << ' ';
            while(l < r) {
                int mid = l + r + 1 >> 1;
//                cout << mid << ' ' << i << ' ' << get(mid, i) << '\n';
                if(get(mid, i) <= st[j].fi)
                    l = mid;
                else r = mid - 1;
            }
//            cout << l << ' ' << i << ' ' << get(l, i) << '\n';
            if(get(l, i) == st[j].fi)
                edge.push_back({l, i, st[j].fi});
        }
        st.pop_back();
        if(i < n) edge.push_back({i, i + 1, p});
    }
    return edge;
}

void solve() {
    cin >> n >> p;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];
    vector <Edge> edge = xuly();
    reverse(a + 1, a + n + 1);
    vector <Edge> nguoc = xuly();
    for(auto [u, v, c] : nguoc) edge.push_back({n - u + 1, n - v + 1, c});
    ll res = 0;
    sort(all(edge));
    for(auto [u, v, c] : edge)
    if(union_sets(u, v)) res += c;
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "1513D"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    int t;
    cin >> t;
    while(t--) solve();
}

