#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()

using namespace std;

typedef long long ll;

const int ar = 2e5+2;
const ll mod = 1e9+7;
const int oo = 1e9;
const int N = 405;

int n, m, a[ar];
int dp[N][N], f[N][N];
struct set3 {
    int l, r, c;
};
vector <set3> g[N];
int s, e, k, c;

void sub1()
{
//    cout << mx << "\n";
    cin >> s >> e >> c >> k;
    ll dau = 1, cuoi = oo, mid, ans, sum;
    int temp;
    bool check;
    while(dau <= cuoi)
    {
        mid = (dau + cuoi) >> 1;
        for(int p = 1; p <= m; p++)
        {
            sum = 0;
            temp = 0;
            check = true;
            for(int i = s + 1; i <= e; i++)
            {
                sum += 1LL * (a[i] - a[i - 1]) * c;
    //            cout << "keke " << " " << sum << "\n";
                if(sum > mid) {
                    temp++;
                    sum = 1LL * (a[i] - a[i - 1]) * c;
                    if(sum > mid) {
                        temp += 200000;
                        break;
                    }
                }
            }
            if(temp > k) {
                check = false;
                break;
            }
        }
        if(check)
        {
            ans = mid;
            cuoi = mid - 1;
        }
        else dau = mid + 1;
    }
    cout << ans;
}

void sub2() {
    for(int i = 1; i <= m; ++i) {
        cin >> s >> e >> c >> k;
        g[k].push_back({s, e, c});
    }

    for(int i = 1; i <= n; ++i)
        for(int j = i + 1; j <= n; ++j)
        f[i][j] = dp[i][j] = a[j] - a[i];

    ll res = 0;
    for(auto [l, r, c] : g[0])
        res = max(res, 1ll * f[l][r] * c);

    for(int k = 1; k <= n; ++k) {
        for(int i = 1; i <= n; ++i) {
            int x = i;
            for(int j = i + 1; j <= n; ++j) {
                dp[i][j] = oo;
                while(x <= j && f[i][x] < a[j] - a[x])
                    dp[i][j] = a[j] - a[x], ++x;
                if(x <= j)
                dp[i][j] = min(dp[i][j], f[i][x]);
            }
        }
        for(int i = 1; i <= n; ++i)
            for(int j = i + 1; j <= n; ++j)
            f[i][j] = dp[i][j];
        for(auto [l, r, c] : g[k])
            res = max(res, 1ll * f[l][r] * c);
    }
    cout << res;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "daily"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];
    if(m == 1)
        sub1();
    else
        sub2();
}
