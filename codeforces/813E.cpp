#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()

using namespace std;

typedef long long ll;

const int ar = 1e5+2;
const ll mod = 1e9+7;
const int oo = 1e9;

queue <int> pos[ar];
int n, k;

struct Node {
    int l = 0, r = 0;
    int cnt = 0;
} st[1 << 22];

int ver[ar], cnt = 0;

int update(int id, int l, int r, int u) {
    int cur = ++cnt;
    if(l == r) {
        st[cur].cnt = st[id].cnt + 1;
//        cout << l << ' ' << cur << ' ' << st[cur].cnt << '\n';
        return cur;
    }

    int mid = l + r >> 1;
    if(mid >= u) {
        st[cur].l = update(st[id].l, l, mid, u);
        st[cur].r = st[id].r;
    }
    else {
        st[cur].l = st[id].l;
        st[cur].r = update(st[id].r, mid + 1, r, u);
    }
    st[cur].cnt = st[st[cur].l].cnt + st[st[cur].r].cnt;
    return cur;
}

int get(int id, int l, int r, int u, int v) {
//    cout << l << ' ' << r << ' ' << id << '\n';
//    cout << st[id].cnt << '\n';
    if(l >= u && r <= v) {
        return st[id].cnt;
    }

    int mid = l + r >> 1;
    int res = 0;
    if(mid >= u) res += get(st[id].l, l, mid, u, v);
    if(mid + 1 <= v) res += get(st[id].r, mid + 1, r, u, v);
    return res;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "813E"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n >> k;
    for(int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        pos[a].push(i);
        int p = 0;
        if(pos[a].size() > k) {
            p = pos[a].front();
            pos[a].pop();
        }
        ver[i] = update(ver[i - 1], 0, n, p);
//        cout << ver[i] << '\n';
    }
//    cout << '\n';

    int q;
    cin >> q;
    int lst = 0;
    while(q--) {
        int l, r;
        cin >> l >> r;
        l = (l + lst) % n + 1;
        r = (r + lst) % n + 1;
        if(l > r) swap(l, r);
//        cout << l << ' ' << r << ' ' << ver[r] << '\n';

        cout << (lst = get(ver[r], 0, n, 0, l - 1) - (l - 1)) << '\n';
    }
}

