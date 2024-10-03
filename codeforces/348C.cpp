#include <bits/stdc++.h>

using namespace std;
#define task "code"

typedef long long ll;

const int ar = 1e5+2;
const ll mod = 1e9+7;
const int oo = 1e9;

int n, m, q, bl = 0, BL, s[ar], id[318], f[318][ar];
ll a[ar], g[318], sum[ar];
vector <int> v[ar];
bool check[318][ar];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	if(fopen(task".inp", "r")) {
		freopen(task".inp", "r", stdin);
		freopen(task".out", "w", stdout);
	}

	cin >> n >> m >> q;
	for(int i = 1; i <= n; ++i)
		cin >> a[i];
	BL = sqrt(n);
	for(int i = 1; i <= m; ++i) {
		cin >> s[i];
		if(s[i] > BL) id[i] = bl++;
		for(int j = 1; j <= s[i]; ++j) {
			int x;
			cin >> x;
			v[i].push_back(x);
			if(s[i] > BL) {
				sum[bl - 1] += a[x];
				// cout << bl << ' ' << a[x] << '\n';
				check[bl - 1][x] = 1;
			}
		}
	}

	for(int i = 0; i < bl; ++i)
		for(int j = 1; j <= m; ++j)
		for(auto x : v[j]) if(check[i][x])
			f[i][j]++;

	while(q--) {
		char c;
		int k, x;
		cin >> c >> k;
		if(c == '?') {
			ll res = 0;
			for(int i = 0; i < bl; ++i)
				res += g[i] * f[i][k];
			if(s[k] > BL) {
				// cout << sum[id[k]] << '\n';
				res += sum[id[k]];
			}
			else for(auto x : v[k]) res += a[x];
			cout << res << '\n';
		}
		else {
			cin >> x;
			if(s[k] > BL) g[id[k]] += x;
			else {
				for(auto y : v[k]) a[y] += x;
				for(int i = 0; i < bl; ++i)
					sum[i] += 1ll * x * f[i][k];
			}
		}
	}
	cout << gcd(1,2);

	return 0;
}
