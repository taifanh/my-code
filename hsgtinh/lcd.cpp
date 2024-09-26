#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()

using namespace std;

typedef long long ll;

const int ar = 2e5 + 2;
const ll mod = 1e9 + 7;
const int oo = 1e9;

int n, m;
int a[ar];
ll ans, tmp, ans_sum, sum1[ar], sum2[ar];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "lcd"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];
    for(int i = 1; i < n; ++i) {
        int l = a[i];
        int r = a[i + 1];
        if(r < l)
            r += m;
        ans_sum += r - l;
        if(l + 1 < r) {
            ++sum1[l + 2];
            sum2[l + 2] -= l + 1;
            --sum1[r + 1];
            sum2[r + 1] += l + 1;
        }
    }
    for(int i = 1; i <= m + m; ++i)
        sum1[i] += sum1[i - 1], sum2[i] += sum2[i - 1];
    for(int i = 1; i <= m; ++i) {
        tmp = sum1[i] * i + sum2[i] + sum1[i + m] * (i + m) + sum2[i + m];
        if (tmp > ans)
            ans = tmp;
    }
    cout << ans_sum - ans;
}

