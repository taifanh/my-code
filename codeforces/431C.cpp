#include <bits/stdc++.h>

using namespace std;
#define task "code"

typedef long long ll;

const int ar = 1e2+2;
const ll mod = 1e9+7;
const int oo = 1e9;

int n, k, d;
ll res = 0, dp[ar][ar][2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	if(fopen(task".inp", "r")) {
		freopen(task".inp", "r", stdin);
		freopen(task".out", "w", stdout);
	}
	
	cin >> n >> k >> d;
	
	dp[0][0][0] = 1;
	for(int i = 1; i <= n; ++i) {
		for(int s = i; s <= n; ++s)
		for(int j = 1; j <= min(k, s); ++j) {
			dp[i][s][0] += dp[i - 1][s - j][0];
			dp[i][s][1] += dp[i - 1][s - j][1];
			if(j >= d) dp[i][s][1] += dp[i - 1][s - j][0];
			dp[i][s][0] %= mod; dp[i][s][1] %= mod;
		}
		res += dp[i][n][1]; res %= mod;
		cout << dp[i][n][1] << ' ';
	}
	cout << res;
	
	return 0;
}