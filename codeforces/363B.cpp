#include <bits/stdc++.h>
//============	Typedef  ================
typedef long long ll;
//============	Define 	================
#define fi first
#define se second
#define task ""
#define pii pair <int, int>
#define pll pair <ll, ll>
//============	Const value ================
const int ar = 1e6+9;
const int mod = 1e9+7;
//==========================================
using namespace std;

int res = 1e9, pos, n, k, a[ar], dp[ar];

//===============  Main  ===================
int main(int argc, char **argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> k;
    for(int i = 1; i <= n; ++i) cin >> a[i], dp[i] = dp[i - 1] + a[i];
    for(int i = 1; i <= n - k + 1; ++i) 
        if(dp[i + k - 1] - dp[i - 1] < res) res = dp[i + k - 1] - dp[i - 1], pos = i;
    cout << pos;

    return 0;
}