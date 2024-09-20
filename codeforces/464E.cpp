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
const int N = 1e5+30;

int n, m;
vector <ii> g[ar];
int mu[N + 5];

struct Node {
    int cnt = 0;
    int val = 0;
    int l = 0, r = 0;
} st[ar * 30];

int nNode = 0, dp[ar], pre[ar];

void refine(int cur) {
    int L = st[cur].l, R = st[cur].r;
    st[cur].cnt = st[L].cnt + st[R].cnt;
    st[cur].val = (st[R].val + st[L].val) % mod;
}

int build(int l, int r, int v) {
    int cur = ++nNode;
    if(l == r) {
        st[cur] = {v, v * mu[l], 0, 0};
        return cur;
    }

    int mid = l + r >> 1;
    st[cur].l = build(l, mid, v);
    st[cur].r = build(mid + 1, r, v);
    refine(cur);
    return cur;
}

int update(int id, int l, int r, int u) {
    int cur = ++nNode;
    if(l == r) {
        st[cur] = {1, mu[l], 0, 0};
        return cur;
    }

    int mid = l + r >> 1;
    st[cur] = st[id];
    if(mid >= u) st[cur].l = update(st[id].l, l, mid, u);
    else st[cur].r = update(st[id].r, mid + 1, r, u);

    refine(cur);

    return cur;
}

int find_zero(int id, int l, int r, int u) {
    if(l == r) {
        if(st[id].cnt == 0) return l;
        return -1;
    }
    int mid = l + r >> 1;

    int res = -1;
    int L = st[id].l, R = st[id].r;
    if(mid >= u && st[L].cnt != mid - l + 1) res = find_zero(L, l, mid, u);
    if(res != -1) return res;
    return find_zero(R, mid + 1, r, u);
}

int dupli(int a, int b, int l, int r, int u, int v) {
    if(l >= u && r <= v) return b;

    int cur = ++nNode;
    int mid = l + r >> 1;
    st[cur] = st[a];
    if(mid >= u) st[cur].l = dupli(st[a].l, st[b].l, l, mid, u, v);
    if(mid + 1 <= v) st[cur].r = dupli(st[a].r, st[b].r, mid + 1, r, u, v);
    refine(cur);
    return cur;
}

bool a_equal_b(int a, int b) {
    if(st[a].cnt == st[b].cnt && st[a].val == st[b].val)
        return 1;
    return 0;
}

bool a_less_b(int a, int b, int l, int r) {
    if(l == r)
        return st[a].cnt <= st[b].cnt;
    int mid = l + r >> 1;
    if(a_equal_b(st[a].r, st[b].r))
        return a_less_b(st[a].l, st[b].l, l, mid);
    return a_less_b(st[a].r, st[b].r, mid + 1, r);
}

struct node {
    int u, val;
};
bool operator < (const node &a, const node &b) {
    return !a_less_b(a.val, b.val, 1, N);
}
priority_queue <node> q;

void dijkstra(int s, int t) {
    int init = build(0, N, 1);
    for(int i = 1; i <= n; ++i) dp[i] = init;
    dp[s] = dp[0] = build(0, N, 0);
    q.push({s, dp[s]});
    while(q.size()) {
        int u = q.top().u, val = q.top().val;
        q.pop();

        if(dp[u] != val) continue;
//        cout << u << ' ' << dp[u] << '\n';

        for(auto [v, w] : g[u]) {
            int p = find_zero(dp[u], 0, N, w);
            int newdp = update(dp[u], 0, N, p);
            if(p > w) newdp = dupli(newdp, dp[0], 0, N, w, p - 1);
            if(!a_less_b(dp[v], newdp, 0, N)) {
                dp[v] = newdp;
                pre[v] = u;
                q.push({v, dp[v]});
            }
        }
    }
    if(dp[t] == init) cout << -1, exit(0);
    cout << st[dp[t]].val << '\n';
    vector <int> trace;
    while(t != s) {
        trace.push_back(t);
        t = pre[t];
    }
    trace.push_back(s);
    cout << trace.size() << '\n';
    reverse(all(trace));
    for(auto x : trace) cout << x << ' ';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "464E"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    mu[0] = 1;
    for(int i = 1; i <= N; ++i)
        mu[i] = mu[i - 1] * 2 % mod;

    int s, t;
    cin >> s >> t;
    dijkstra(s, t);
}
