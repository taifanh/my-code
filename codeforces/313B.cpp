#include <bits/stdc++.h>
//============	Typedef  ================
typedef long long ll;
//============	Define 	================
#define fi first
#define se second
#define pii pair <int, int>
#define pll pair <ll, ll>
//============	Const value ================
const int ar = 1e6+9;
const int mod = 1e9+7;
//==========================================
using namespace std;

string s;
int dp[ar], l, r, m;

//===============  Main  ===================
int main(int argc, char **argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> s;
    for(int i = 0; i < s.size() - 1; ++i)
        dp[i + 1] = dp[i] + (s[i] == s[i + 1]);
    cin >> m;
    while(m--) {
        cin >> l >> r;
        cout << dp[r - 1] - dp[l - 1] << '\n';
    }

    return 0;
}