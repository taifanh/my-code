#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int ar = 2e5+2;

int n;
ll a[ar];

signed main() {
    int t;
    cin >> t;
    while(t--) {
        cin >> n;
        for(int i = 1; i <= n; ++i)
            cin >> a[i];
        for(int i = 1; i <= n - 2; ++i)
            a[n - 1] -= a[i];
        cout << a[n] - a[n - 1] << '\n';
    }
}

