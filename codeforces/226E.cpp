#include <bits/stdc++.h>
#define ll long long
#define ii pair <int, int>
#define fi first
#define se second

using namespace std;

const int ar = 2e5+5;
const int LG = 18;

int n, m = 0, in[ar], out[ar];
vector <int> g[ar];
int h[ar], up[ar][LG + 1];

void dfs(int u) {
    in[u] = ++m;
    for(int v : g[u]) if(v != up[u][0]){
        h[v] = h[u] + 1;
        up[v][0] = u;
        for(int j = 1; j <= LG; ++j)
            up[v][j] = up[up[v][j - 1]][j - 1];
        dfs(v);
    }
    out[u] = m;
}

int park(int u, int k) {
    for(int j = 0; (1 << j) <= k; ++j)
        if(k & (1 << j)) u = up[u][j];
    return u;
}

int lca(int u, int v) {
    if(h[u] != h[v]) {
        if(h[u] < h[v]) swap(u, v);
        u = park(u, h[u] - h[v]);
    }
    if(u == v) return u;

    int k = 31 - __builtin_clz(h[u]);
    for(int j = k; j >= 0; --j)
    if(up[u][j] != up[v][j]) {
        u = up[u][j];
        v = up[v][j];
    }
    return up[u][0];
}

struct Node {
    int cnt = 0;
    int l = 0, r = 0;
} st[1 << 22];

int ver[ar], nNode = 0;

void refine(int id) {
    st[id].cnt = st[st[id].l].cnt + st[st[id].r].cnt;
}

int update(int id, int l, int r, int u, int v) {
    int cur = ++nNode;
    if(l == r) {
        st[cur].cnt = st[id].cnt + v;
        return cur;
    }

    int mid = l + r >> 1;
    st[cur] = st[id];
    if(mid >= u) st[cur].l = update(st[id].l, l, mid, u, v);
    else st[cur].r = update(st[id].r, mid + 1, r, u, v);
    refine(cur);
    return cur;
}

int get(int lid, int rid, int l, int r, int u, int v) {
    if(u > v) return 0;
    if(l >= u && r <= v) return st[rid].cnt - st[lid].cnt;

    int mid = l + r >> 1;
    int res = 0;
    if(mid >= u) res += get(st[lid].l, st[rid].l, l, mid, u, v);
    if(mid + 1 <= v) res += get(st[lid].r, st[rid].r, mid + 1, r, u, v);
    return res;
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    #define task "226E"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        int p;
        cin >> p;
        if(p == 0) continue;
        g[i].push_back(p);
        g[p].push_back(i);
    }
    h[0] = -1;
    dfs(1);

    int q, t, a, b, k, y;
    cin >> q;
    for(int i = 1; i <= q; ++i) {
        ver[i] = ver[i - 1];
        cin >> t >> a;
        if(t == 1) {
            ver[i] = update(ver[i - 1], 1, m, in[a], 1);
            ver[i] = update(ver[i], 1, m, out[a], -1);
        }
        else {
            cin >> b >> k >> y;
            int p =  lca(a, b);
            int cnt = h[a] - h[p] + h[b] - h[p] - 1;
            int l = 1, r = cnt, res = -1;
            while(l <= r) {
                int mid = l + r >> 1;
                int ok = 0;
                if(in[a] < in[b] && out[a] > out[b]) {
                    int anc = park(b, cnt - mid + 1);
                    ok = get(ver[y], ver[i], 1, m, in[a] + 1, in[anc]);
                    ok = h[anc] - h[a] - ok;
                }
                else if(in[a] > in[b] && out[a] < out[b]) {
                    int anc = park(a, mid);
                    ok = get(ver[y], ver[i], 1, m, in[anc], in[up[a][0]]);
                    ok = h[a] - h[anc] - ok;
                }
                else {
                    int anc = park(a, mid);
                    if(h[anc] < h[p]) {
                        anc = park(b, cnt - mid + 1);
                        ok = get(ver[y], ver[i], 1, m, in[p] + 1, in[anc]) + get(ver[y], ver[i], 1, m, in[p], in[up[a][0]]);
                        ok = h[anc] - h[p] + h[a] - h[p] - ok;
                    }
                    else {
                        ok = get(ver[y], ver[i], 1, m, in[anc], in[up[a][0]]);
                        ok = h[a] - h[anc] - ok;
                    }
                }
                if(ok >= k)
                    res = mid, r = mid - 1;
                else l = mid + 1;
            }
            if(res == -1) {
                cout << res << '\n';
                continue;
            }
            int anc = park(a, res);
            if(h[anc] < h[p]) anc = park(b, cnt - res + 1);
            cout << anc << '\n';
        }
    }
}
