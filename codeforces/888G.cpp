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
const int oo = 2e9;

int cnt = 0;
ll res = 0;
int n;
vector <int> a, tap[ar];

int lab[ar];
ii cost[ar];

int find_set(int u) {
    return lab[u] < 0 ? u : lab[u] = find_set(lab[u]);
}

void union_sets(int u, int v, ll val) {
    u = find_set(u);
    v = find_set(v);
    if(u != v) {
        if(lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
//        cout << u << ' ' << v << ' ' << val << '\n';
        res += val;
        cnt++;
    }
}

int nNode = 0;
struct Node {
    int child[2];
    int id;
    int cnt;
    Node() {
        memset(child, -1, sizeof child);
        id = cnt = 0;
    }
} node[60 * ar];

void add(int val, int pos) {
    int p = 0;
    for(int i = 30; i >= 0; --i) {
        int x = val >> i & 1;
        if(node[p].child[x] == -1) node[p].child[x] = ++nNode;
        p = node[p].child[x];
        node[p].cnt++;
    }
    node[p].id = pos;
}

void del(int val) {
    int p = 0;
    for(int i = 30; i >= 0; --i) {
        int x = val >> i & 1;
        p = node[p].child[x];
        node[p].cnt--;
    }
}

ii get(int val) {
    int p = 0, ans = 0;
    for(int i = 30; i >= 0; --i) {
        int x = val >> i & 1;
        if(node[p].child[x] != -1 && node[node[p].child[x]].cnt)
            p = node[p].child[x];
        else {
//            cout << i << ' ';
            p = node[p].child[x ^ 1];
            ans |= (1 << i);
        }
    }
//    cout << ans << '\n';
    return {ans, node[p].id};
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "888G"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n;
    a.resize(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    sort(all(a));
    a.resize(unique(all(a)) - a.begin());
    n = a.size();

    for(int i = 0; i < n; ++i) {
        lab[i] = -1;
        add(a[i], i);
    }

    while(cnt < n - 1) {
        for(int i = 0; i < n; ++i) {
            tap[find_set(i)].push_back(i);
//            cout << find_set(i) << ' ';
            cost[i] = {oo, -1};
        }
//        cout << '\n';

        for(int i = 0; i < n; ++i) {
            for(auto j : tap[i])
                del(a[j]);
            for(auto j : tap[i]) {
//                cout << j << ' ';
                cost[i] = min(cost[i], get(a[j]));
//                cout << get(a[j]).fi << ' ' << get(a[j]).se << '\n';
            }
            for(auto j : tap[i])
                add(a[j], j);
        }

        for(int i = 0; i < n; ++i) {
            tap[i].clear();
            if(cost[i].se == -1) continue;
//            cout << cost[i].fi << ' ';
            union_sets(i, cost[i].se, cost[i].fi);
        }
//        cout << "\n\n";
    }
    cout << res;
}

