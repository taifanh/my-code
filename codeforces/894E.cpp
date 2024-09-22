#include <bits/stdc++.h>
#define ll long long
#define ii pair <ll, int>

using namespace std;

const int ar = 1e6+2;
const int mod = 1e9+7;

int n, m, s;
ll a[ar];
vector <ii> g[ar], h[ar];
bool vs[ar];
int scc = 0, low[ar], num[ar], timeDfs = 0, tplt[ar];
ll pre[ar];
stack <int> st;
ll fval[ar], dp[ar];

int giaiPT(ll a, ll b, ll c,ll &x1, ll &x2){
	double delta = b*b - 4*a*c;
	if(delta<0){
		x1=x2=0;
		return 0;
	}
	else if(delta==0){
		x1 = x2 = -b/(2*a);
		return 1;
	}
	else{
		delta = sqrt(delta);
		x1 = (-b + delta) / (2*a);
		x2 = (-b - delta) / (2*a);
		return 2;
	}
}

ll xuly(ll vv) {
    ll x1, x2;
    int kq = giaiPT(1, 1, -vv*2, x1, x2);
    if(kq == 2) {
        if(x1 < x2) swap(x1, x2);
    }
    return vv * (x1 + 1) - pre[x1];
}

vector <int> luu[ar];
void dfs(int u) {
  num[u] = low[u] = ++timeDfs;
  st.push(u);
  for (auto &[w, v] : g[u]) if(!tplt[v]){
    if (!num[v]){
      dfs(v);
      low[u] = min(low[u], low[v]);
    }
    else {
        low[u] = min(low[u], num[v]);
    }
  }
  if (low[u] == num[u]) {
    scc++;
    while(1) {
    	int v = st.top();
    	st.pop();
    	luu[scc].push_back(v);
    	tplt[v] = scc;
    	if(u == v) break;
    }
  }
}

void duyet(int u) {
    vs[u] = 1;
    for(auto &[w, v] : g[u]) {
//        cout << u << ' ' << v << '\n';
        if(tplt[v] == tplt[u]) fval[tplt[u]] += xuly(w);
        if(!vs[v]) duyet(v);
    }
}

vector <int> topo;
int xp[ar];
void xeptopo(int u) {
    vs[u] = 1;
    for (auto &[w, v] : h[u]) {
        if (!vs[v]) xeptopo(v);
    }
    topo.push_back(u);
}

map <int, int> mp[ar];
struct set3 {
    int u, v;
} po[ar];

int main() {
    if(fopen("code.inp", "r")) {
        freopen("code.inp", "r", stdin);
        freopen("code.out", "w", stdout);
    }
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    cin >> m;
    for(ll i = 1; i * (i + 1) / 2 <= 100000000; ++i)
        pre[i] = pre[i - 1] + i * (i + 1) / 2;
    for(int i = 1; i <= m; ++i) {
        int w;
        cin >> po[i].u >> po[i].v >> w;
//        mp[po[i].u][po[i].v] = max(mp[po[i].u][po[i].v],w);
        g[po[i].u].push_back({w, po[i].v});
    }
//    for(int i = 1; i <= m; ++i)
//    if(mp[po[i].u][po[i].v] != 0)
//    g[po[i].u].push_back({mp[po[i].u][po[i].v], po[i].v}),
//    mp[po[i].u][po[i].v] = 0;
    cin >> s;

    for(int i = 1; i <= n; ++i)
        if(!num[i]) dfs(i);

    for(int u = 1; u <= n; ++u) {
//        cout << tplt[u] << ' ';
        for(auto &[w, v] : g[u])
            if(tplt[u] != tplt[v]) {
                h[tplt[u]].push_back({w, tplt[v]});
            }
        if(!vs[u]) duyet(u);
//        cout << tplt[u] << ' ';
    }
//    cout << '\n';
   	for(int i = 1; i <= scc; ++i) {
//        for(auto &[w, _] : h[i])
//            cout << w << ' '; cout << '\n';
   		sort(h[i].begin(), h[i].end());
   		h[i].resize(unique(h[i].begin(), h[i].end()) - h[i].begin());
//        cout << fval[i] << ' ';
   	}
//   	cout << '\n';
    memset(vs, 0, sizeof vs);
   	xeptopo(tplt[s]);
    reverse(topo.begin(), topo.end());
    xp[tplt[s]] = tplt[s];
    dp[tplt[s]] = fval[tplt[s]];
    ll res = dp[tplt[s]];
//    for(auto u : topo) cout << u << ' ';
//    cout << '\n';

    for(int i = 1; i < topo.size(); ++i) {
        int u = topo[i - 1];
        if(xp[u] != tplt[s]) continue;
        for(auto &[w, v] : h[u]) {
            xp[v] = tplt[s];
//            ll tmp = xuly(w);
            if(dp[v] < dp[u] + fval[v] + w)
                dp[v] = dp[u] + fval[v] + w;
        }
        res = max(res, dp[topo[i]]);
    }
    cout << res;

    return 0;
}
