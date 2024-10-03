#include <bits/stdc++.h>

typedef long long ll;

const int ar = 2e5+9;
const int mod = 1e9+7;
const int oo = 1e9;

using namespace std;

int n, q, l, r, a[ar];
vector <int> v[ar];
ll cal[ar], res = 0, f[ar];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    while(q--) {
        cin >> l >> r;
        f[l]++;
        f[r + 1]--;
    }

    for(int i = 1; i <= n; ++i)
        f[i] += f[i - 1], v[f[i]].push_back(i);
    
    sort(a + 1, a + n + 1, greater <int> ());

    int j = 0;
    for(int i = n; i >= 0; --i)
        for(auto x : v[i])
            cal[x] = a[++j];
    
    for(int i = 1; i <= n; ++i)
        res += cal[i] * f[i];
    cout << res;

    return 0;
}